/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/06 11:23:15 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(t_app *app)
{
	free_app(app);
	exit(0);
}

int	key_press(int keycode, t_app *app)
{
	if (keycode == KEY_W)
		app->keys.w = TRUE;
	else if (keycode == KEY_A)
		app->keys.a = TRUE;
	else if (keycode == KEY_S)
		app->keys.s = TRUE;
	else if (keycode == KEY_D)
		app->keys.d = TRUE;
	else if (keycode == KEY_LEFT)
		app->keys.left = TRUE;
	else if (keycode == KEY_RIGHT)
		app->keys.right = TRUE;
	else if (keycode == KEY_ESC)
		return (close_window(app));
	return (0);
}

int	key_release(int keycode, t_app *app)
{
	if (keycode == KEY_W)
		app->keys.w = FALSE;
	else if (keycode == KEY_A)
		app->keys.a = FALSE;
	else if (keycode == KEY_S)
		app->keys.s = FALSE;
	else if (keycode == KEY_D)
		app->keys.d = FALSE;
	else if (keycode == KEY_LEFT)
		app->keys.left = FALSE;
	else if (keycode == KEY_RIGHT)
		app->keys.right = FALSE;
	return (0);
}
