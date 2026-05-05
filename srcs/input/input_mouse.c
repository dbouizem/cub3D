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

/*
** Bonus hooks:
** mouse weapon/minimap controls are ignored while retro bonus mode is disabled.
*/
int	handle_mouse_press(int button, int x, int y, t_app *app)
{
	(void)x;
	(void)y;
	if (!app || app->bonus.retro.enabled == 0)
		return (0);
	if (button == BUTTON_LEFT)
		bonus_hud_try_fire(app);
	else if (button == BUTTON_SCROLL_UP)
	{
		app->bonus.retro.minimap_zoom += BONUS_MINIMAP_ZOOM_STEP;
		if (app->bonus.retro.minimap_zoom > BONUS_MINIMAP_ZOOM_MAX)
			app->bonus.retro.minimap_zoom = BONUS_MINIMAP_ZOOM_MAX;
	}
	else if (button == BUTTON_SCROLL_DOWN)
	{
		app->bonus.retro.minimap_zoom -= BONUS_MINIMAP_ZOOM_STEP;
		if (app->bonus.retro.minimap_zoom < BONUS_MINIMAP_ZOOM_MIN)
			app->bonus.retro.minimap_zoom = BONUS_MINIMAP_ZOOM_MIN;
	}
	return (0);
}

/*
** Bonus hook:
** mouse look is disabled in mandatory mode because app->bonus.retro.enabled is 0.
*/
int	handle_mouse_move(int x, int y, t_app *app)
{
	(void)y;
	if (!app || app->bonus.retro.enabled == 0 || x < 0 || x >= app->win_w)
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

/*
** Bonus hook:
** mandatory never applies mouse rotation because the bonus flag stays disabled.
*/
void	apply_mouse_look(t_app *app)
{
	double	angle;

	if (!app || app->bonus.retro.enabled == 0 || !app->input.mouse_ready)
		return ;
	if (app->input.mouse_dx == 0)
		return ;
	angle = (double)app->input.mouse_dx * BONUS_MOUSE_SENS;
	rotate_mouse(app, angle);
	app->input.mouse_dx = 0;
}
