/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_trace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeceiro <bbeceiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:31:14 by bbeceiro          #+#    #+#             */
/*   Updated: 2026/05/07 14:31:16 by bbeceiro         ###   ########.fr       */
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

void	trace_ray(t_app *app, t_ray *ray)
{
	run_dda(app, ray);
	calculate_ray_result(app, ray);
}
