/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeceiro <bbeceiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 05:20:00 by bbeceiro            #+#    #+#             */
/*   Updated: 2026/04/05 05:20:00 by bbeceiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_ray(t_app *app, t_ray *r, int x)
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
	if (r->ray_dir_x < 0)
		r->side_x = (app->player.x - r->map_x) * r->delta_x;
	else
		r->side_x = (r->map_x + 1.0 - app->player.x) * r->delta_x;
	if (r->ray_dir_y < 0)
		r->side_y = (app->player.y - r->map_y) * r->delta_y;
	else
		r->side_y = (r->map_y + 1.0 - app->player.y) * r->delta_y;
}

/*
** Bonus hooks:
** mandatory treats only '1' as solid and has no doors.
*/
static int	hit_solid_cell(t_app *app, t_ray *r)
{
	double	dist;
	double	hit;
	char	tile;

	tile = bonus_map_cell_at(app, r->map_x, r->map_y);
	if (tile == ' ')
		return (1);
	if (!bonus_is_door_tile(tile))
		return (bonus_is_solid_tile(tile));
	if (r->side == 0)
		dist = r->side_x - r->delta_x;
	else
		dist = r->side_y - r->delta_y;
	if (r->side == 0)
		hit = app->player.y + dist * r->ray_dir_y;
	else
		hit = app->player.x + dist * r->ray_dir_x;
	hit -= floor(hit);
	return (!bonus_door_allows_passage_at(app, r->map_x, r->map_y, hit));
}

static void	step_dda(t_ray *r)
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

static t_ray	cast_ray(t_app *app, int x)
{
	t_ray	r;
	int		guard;

	setup_ray(app, &r, x);
	guard = 0;
	while (guard++ < 16384)
	{
		step_dda(&r);
		if (hit_solid_cell(app, &r))
			break ;
	}
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

/*
** Bonus hook:
** mandatory does not store sprite depth; bonus uses it to sort sprites.
*/
int	raycast_scene(t_app *app)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < app->frame.width)
	{
		ray = cast_ray(app, x);
		draw_wall_column(app, ray);
		bonus_sprites_set_depth(app, x, ray.perp_dist);
		x++;
	}
	return (0);
}
