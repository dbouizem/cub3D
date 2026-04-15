/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/15 10:27:17 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_app *app, t_ray *ray, int x)
{
	ray->camera_x = 2.0 * x / (double)app->win_w - 1.0;
	ray->ray_dir_x = app->dir_x + app->plane_x * ray->camera_x;
	ray->ray_dir_y = app->dir_y + app->plane_y * ray->camera_x;
	ray->map_x = (int)(app->player_x + 1e-9);
	ray->map_y = (int)(app->player_y + 1e-9);
	ray->hit = 0;
	ray->side = 0;
	ray->wall_face = '\0';
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

void	prepare_dda(t_app *app, t_ray *ray)
{
	init_delta_dist(ray);
	init_step_x(app, ray);
	init_step_y(app, ray);
}
