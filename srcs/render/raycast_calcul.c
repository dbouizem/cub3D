/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_calcul.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:30:01 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/15 10:30:54 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_wall_x(t_app *app, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = app->player_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = app->player_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= (double)((int)wall_x);
	ray->wall_x = wall_x;
}
// TEST to debug, using fabs()
static void	calculate_wall_distance(t_app *app, t_ray *ray)
{
	double	dist;

	if (ray->side == 0)
		dist = (ray->map_x - app->player_x + (1 - ray->step_x) / 2.0)
				/ ray->ray_dir_x;
	else
		dist = (ray->map_y - app->player_y + (1 - ray->step_y) / 2.0)
				/ ray->ray_dir_y;
	ray->perp_wall_dist = fabs(dist);
	if (ray->perp_wall_dist < 0.01)
		ray->perp_wall_dist = 0.01;
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

void	calculate_ray_result(t_app *app, t_ray *ray)
{
	calculate_wall_distance(app, ray);
	calculate_wall_x(app, ray);
	calculate_wall_slice(app, ray);
	detect_wall_face(ray);
}
