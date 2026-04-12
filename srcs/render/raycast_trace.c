/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_trace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/12 00:00:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	detect_wall_face(t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->wall_face = 'W';
	else if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->wall_face = 'E';
	else if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->wall_face = 'N';
	else if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->wall_face = 'S';
}

void	trace_ray(t_app *app, t_ray *ray)
{
	run_dda(app, ray);
	calculate_wall_distance(app, ray);
	calculate_wall_slice(app, ray);
	detect_wall_face(ray);
}
