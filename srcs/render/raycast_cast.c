/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_cast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 05:20:00 by brrr1            #+#    #+#             */
/*   Updated: 2026/04/05 05:20:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_app *app, int x, int y)
{
	int	len;

	if (y < 0 || y >= app->map.height)
		return (1);
	len = (int)ft_strlen(app->map.grid[y]);
	if (x < 0 || x >= len)
		return (1);
	return (bonus_is_solid_tile(app->map.grid[y][x]));
}

static void	init_ray(t_app *app, t_ray *r, int x)
{
	r->x = x;
	r->camera_x = 2.0 * x / (double)app->frame.width - 1.0;
	r->ray_dir_x = app->dir_x + app->plane_x * r->camera_x;
	r->ray_dir_y = app->dir_y + app->plane_y * r->camera_x;
	r->map_x = (int)app->player.x;
	r->map_y = (int)app->player.y;
	r->delta_x = fabs(1.0 / r->ray_dir_x);
	r->delta_y = fabs(1.0 / r->ray_dir_y);
	r->step_x = -1;
	r->step_y = -1;
	if (r->ray_dir_x >= 0)
		r->step_x = 1;
	if (r->ray_dir_y >= 0)
		r->step_y = 1;
}

static void	run_dda(t_app *app, t_ray *r)
{
	if (r->ray_dir_x < 0)
		r->side_x = (app->player.x - r->map_x) * r->delta_x;
	else
		r->side_x = (r->map_x + 1.0 - app->player.x) * r->delta_x;
	if (r->ray_dir_y < 0)
		r->side_y = (app->player.y - r->map_y) * r->delta_y;
	else
		r->side_y = (r->map_y + 1.0 - app->player.y) * r->delta_y;
	while (is_wall(app, r->map_x, r->map_y) == 0)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
	}
}

t_ray	cast_ray(t_app *app, int x)
{
	t_ray	r;

	init_ray(app, &r, x);
	run_dda(app, &r);
	if (r.side == 0)
		r.perp_dist = r.side_x - r.delta_x;
	else
		r.perp_dist = r.side_y - r.delta_y;
	r.line_height = (int)(app->frame.height / (r.perp_dist + 1e-9));
	if (r.line_height < 1)
		r.line_height = 1;
	r.draw_start = -r.line_height / 2 + app->frame.height / 2;
	if (r.draw_start < 0)
		r.draw_start = 0;
	r.draw_end = r.line_height / 2 + app->frame.height / 2;
	if (r.draw_end >= app->frame.height)
		r.draw_end = app->frame.height - 1;
	return (r);
}
