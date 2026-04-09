/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:10:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 13:10:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_mouse(t_app *app, double angle)
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

int	handle_mouse_move(int x, int y, t_app *app)
{
	(void)y;
	if (!app || app->bonus_on == 0 || x < 0 || x >= app->win_w)
		return (0);
	if (!app->input.mouse_ready)
	{
		app->input.mouse_ready = 1;
		app->input.mouse_last_x = x;
		return (0);
	}
	app->input.mouse_dx += (x - app->input.mouse_last_x);
	app->input.mouse_last_x = x;
	return (0);
}

void	apply_mouse_look(t_app *app)
{
	double	angle;

	if (!app || app->bonus_on == 0 || !app->input.mouse_ready)
		return ;
	if (app->input.mouse_dx == 0)
		return ;
	angle = (double)app->input.mouse_dx * BONUS_MOUSE_SENS;
	rotate_mouse(app, angle);
	app->input.mouse_dx = 0;
}
