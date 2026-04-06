/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 05:20:00 by brrr1            #+#    #+#             */
/*   Updated: 2026/04/05 05:20:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*pick_texture(t_app *app, t_ray ray)
{
	if (ray.side == 0)
	{
		if (ray.ray_dir_x > 0)
			return (&app->tex_we);
		return (&app->tex_ea);
	}
	if (ray.ray_dir_y > 0)
		return (&app->tex_no);
	return (&app->tex_so);
}

static int	sample_texel(t_img *tex, int tex_x, int tex_y)
{
	char	*pixel;

	if (tex->img_ptr == NULL || tex->addr == NULL)
		return (0x00FFFFFF);
	if (tex->width <= 0 || tex->height <= 0)
		return (0x00FFFFFF);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if (tex_y >= tex->height)
		tex_y = tex->height - 1;
	pixel = tex->addr + (tex_y * tex->line_len + tex_x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

static int	texture_x(t_ray ray, t_img *tex, double wall_x)
{
	int	x;

	x = (int)(wall_x * (double)tex->width);
	if ((ray.side == 0 && ray.ray_dir_x < 0)
		|| (ray.side == 1 && ray.ray_dir_y > 0))
		x = tex->width - x - 1;
	return (x);
}

static void	draw_wall_texels(t_app *app, t_ray ray, t_img *tex, double wall_x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_x;

	step = (double)tex->height / (double)ray.line_height;
	tex_pos = (ray.draw_start - app->frame.height / 2
			+ ray.line_height / 2) * step;
	tex_x = texture_x(ray, tex, wall_x);
	y = ray.draw_start;
	while (y <= ray.draw_end)
	{
		put_pixel(&app->frame, ray.x, y,
			sample_texel(tex, tex_x, (int)tex_pos));
		tex_pos += step;
		y++;
	}
}

void	draw_wall_column(t_app *app, t_ray ray)
{
	t_img	*tex;
	double	wall_x;

	tex = pick_texture(app, ray);
	if (ray.line_height <= 0 || app->frame.height <= 0)
		return ;
	if (ray.side == 0)
		wall_x = app->player.y + ray.perp_dist * ray.ray_dir_y;
	else
		wall_x = app->player.x + ray.perp_dist * ray.ray_dir_x;
	draw_wall_texels(app, ray, tex, wall_x - floor(wall_x));
}
