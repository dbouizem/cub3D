/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 11:02:13 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr || x < 0 || y < 0
		|| x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

static void	clear_frame(t_app *app)
{
	int	x;
	int	y;

	y = 0;
	while (y < app->win_h)
	{
		x = 0;
		while (x < app->win_w)
		{
			if (y < app->win_h / 2)
				put_pixel(&app->frame, x, y, app->ceiling_color);
			else
				put_pixel(&app->frame, x, y, app->floor_color);
			x++;
		}
		y++;
	}
}

static void	init_ray(t_app *app, t_ray *ray, int x)
{
	ray->camera_x = 2.0 * x / (double)app->win_w - 1.0;
	ray->ray_dir_x = app->dir_x + app->plane_x * ray->camera_x;
	ray->ray_dir_y = app->dir_y + app->plane_y * ray->camera_x;
	ray->map_x = (int)app->player_x;
	ray->map_y = (int)app->player_y;
	ray->hit = 0;
	ray->side = 0;
	ray->perp_wall_dist = 0.0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

static void	init_delta_dist(t_ray *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
}

static void	init_step_x(t_app *app, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (app->player_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - app->player_x)
			* ray->delta_dist_x;
	}
}

static void	init_step_y(t_app *app, t_ray *ray)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (app->player_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - app->player_y)
			* ray->delta_dist_y;
	}
}

static void	prepare_dda(t_app *app, t_ray *ray)
{
	init_delta_dist(ray);
	init_step_x(app, ray);
	init_step_y(app, ray);
}

static char	get_map_cell(t_app *app, int map_x, int map_y)
{
	int	row_len;

	if (map_y < 0 || map_y >= app->map_height)
		return (' ');
	row_len = ft_strlen(app->file_lines[app->map_start + map_y]);
	if (map_x < 0 || map_x >= row_len)
		return (' ');
	return (app->file_lines[app->map_start + map_y][map_x]);
}

static void	run_dda(t_app *app, t_ray *ray)
{
	char	cell;

	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		cell = get_map_cell(app, ray->map_x, ray->map_y);
		if (cell == '1' || cell == ' ')
			ray->hit = 1;
	}
}

static void	calculate_wall_distance(t_app *app, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - app->player_x
				+ (1 - ray->step_x) / 2.0) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - app->player_y
				+ (1 - ray->step_y) / 2.0) / ray->ray_dir_y;
	if (ray->perp_wall_dist <= 0.0)
		ray->perp_wall_dist = 0.0001;
}

static void	calculate_wall_slice(t_app *app, t_ray *ray)
{
	ray->line_height = (int)(app->win_h / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + app->win_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + app->win_h / 2;
	if (ray->draw_end >= app->win_h)
		ray->draw_end = app->win_h - 1;
}

static void	draw_wall_column(t_app *app, t_ray *ray, int x)
{
	int	y;
	int	color;

	if (ray->side == 0)
		color = 0x00CC6666;
	else
		color = 0x00884444;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		put_pixel(&app->frame, x, y, color);
		y++;
	}
}

static void	prepare_rays(t_app *app)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < app->win_w)
	{
		init_ray(app, &ray, x);
		prepare_dda(app, &ray);
		run_dda(app, &ray);
		calculate_wall_distance(app, &ray);
		calculate_wall_slice(app, &ray);
		draw_wall_column(app, &ray, x);
		x++;
	}
}

int	draw_frame(t_app *app)
{
	handle_movement(app);
	handle_rotation(app);
	clear_frame(app);
	prepare_rays(app);
	mlx_put_image_to_window(app->mlx_ptr, app->win_ptr,
		app->frame.img_ptr, 0, 0);
	return (0);
}
