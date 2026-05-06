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

/*
** Bonus hook:
** mandatory gets NULL here and falls back to NO/SO/WE/EA textures.
*/
static t_img	*pick_texture(t_app *app, t_ray ray)
{
	t_img	*bonus_tex;
	char	tile;

	tile = bonus_map_cell_at(app, ray.map_x, ray.map_y);
	bonus_tex = bonus_pick_wall_texture(app, tile);
	if (bonus_tex != NULL)
		return (bonus_tex);
	if (ray.side == 0 && ray.ray_dir_x > 0)
		return (&app->tex_we);
	if (ray.side == 0)
		return (&app->tex_ea);
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

/*
** Bonus hook:
** mandatory door progress is 0, so this projection does not modify walls.
*/
static void	apply_door_projection(t_ray *ray, double *wall_x, char tile,
	double progress)
{
	double	panel;
	double	half;

	if (progress <= 0.0 || progress >= 1.0)
		return ;
	if (tile == 'A')
	{
		ray->draw_end -= (int)((double)ray->line_height * progress);
		return ;
	}
	half = progress * 0.5;
	panel = 0.5 - half;
	if (panel <= 1e-6)
		return ;
	if (*wall_x < 0.5)
		*wall_x = (*wall_x / panel) * 0.5;
	else
		*wall_x = 0.5 + ((*wall_x - (0.5 + half)) / panel) * 0.5;
	if (*wall_x < 0.0)
		*wall_x = 0.0;
	if (*wall_x > 1.0)
		*wall_x = 1.0;
}

static void	draw_wall_texels(t_app *app, t_ray ray, t_img *tex, double wall_x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_x;
	int		color;

	step = (double)tex->height / (double)ray.line_height;
	tex_pos = (ray.draw_start - app->frame.height / 2
			+ ray.line_height / 2) * step;
	tex_x = (int)(wall_x * (double)tex->width);
	if ((ray.side == 0 && ray.ray_dir_x < 0)
		|| (ray.side == 1 && ray.ray_dir_y > 0))
		tex_x = tex->width - tex_x - 1;
	y = ray.draw_start;
	while (y <= ray.draw_end)
	{
		color = sample_texel(tex, tex_x, (int)tex_pos);
		color = apply_wall_shading(color, ray);
		put_pixel(&app->frame, ray.x, y, color);
		tex_pos += step;
		y++;
	}
}

void	draw_wall_column(t_app *app, t_ray ray)
{
	t_img	*tex;
	char	tile;
	double	wall_x;
	double	progress;

	tex = pick_texture(app, ray);
	if (ray.line_height <= 0 || app->frame.height <= 0)
		return ;
	if (ray.side == 0)
		wall_x = app->player.y + ray.perp_dist * ray.ray_dir_y;
	else
		wall_x = app->player.x + ray.perp_dist * ray.ray_dir_x;
	wall_x = wall_x - floor(wall_x);
	tile = bonus_map_cell_at(app, ray.map_x, ray.map_y);
	progress = bonus_door_open_progress_at(app, ray.map_x, ray.map_y);
	apply_door_projection(&ray, &wall_x, tile, progress);
	if (ray.draw_end < ray.draw_start)
		return ;
	draw_wall_texels(app, ray, tex, wall_x);
}
