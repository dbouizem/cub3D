/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeceiro <bbeceiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 05:20:00 by bbeceiro            #+#    #+#             */
/*   Updated: 2026/04/05 05:20:00 by bbeceiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_player(t_app *app, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = app->dir_x;
	old_plane_x = app->plane_x;
	app->dir_x = app->dir_x * cos(angle) - app->dir_y * sin(angle);
	app->dir_y = old_dir_x * sin(angle) + app->dir_y * cos(angle);
	app->plane_x = app->plane_x * cos(angle) - app->plane_y * sin(angle);
	app->plane_y = old_plane_x * sin(angle) + app->plane_y * cos(angle);
}

void	rotate_left(t_app *app)
{
	rotate_player(app, -ROT_SPEED * app->delta_time);
}

void	rotate_right(t_app *app)
{
	rotate_player(app, ROT_SPEED * app->delta_time);
}
