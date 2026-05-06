/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/05 05:20:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_move_keys(t_app *app, int keycode, int value)
{
	if (keycode == KEY_W || keycode == KEY_Z)
		app->input.forward = value;
	else if (keycode == KEY_S)
		app->input.backward = value;
	else if (keycode == KEY_A || keycode == KEY_Q)
		app->input.left = value;
	else if (keycode == KEY_D)
		app->input.right = value;
}

static void	set_turn_keys(t_app *app, int keycode, int value)
{
	if (keycode == KEY_LEFT)
		app->input.turn_left = value;
	else if (keycode == KEY_RIGHT)
		app->input.turn_right = value;
}

/*
** Bonus hooks:
** F1/F2/F3, F4, E, and SPACE do nothing in mandatory mode because they call
** no-op hooks.
*/
int	handle_keypress(int keycode, t_app *app)
{
	if (keycode == KEY_ESC)
		close_window(app);
	if (keycode == KEY_F4)
	{
		if (bonus_load_next_level(app) == 0)
			return (0);
	}
	if (keycode == KEY_E)
		bonus_door_try_toggle(app);
	if (keycode == KEY_SPACE)
		bonus_hud_try_fire(app);
	if (bonus_apply_resolution_preset(app, keycode))
		return (0);
	set_move_keys(app, keycode, 1);
	set_turn_keys(app, keycode, 1);
	return (0);
}

int	handle_keyrelease(int keycode, t_app *app)
{
	set_move_keys(app, keycode, 0);
	set_turn_keys(app, keycode, 0);
	return (0);
}
