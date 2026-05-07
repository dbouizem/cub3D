/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeceiro <bbeceiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:28:13 by bbeceiro          #+#    #+#             */
/*   Updated: 2026/05/07 14:28:16 by bbeceiro         ###   ########.fr       */
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
	if (keycode == KEY_W || keycode == KEY_Z)
		app->keys.w = TRUE;
	else if (keycode == KEY_A || keycode == KEY_Q)
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
	if (keycode == KEY_W || keycode == KEY_Z)
		app->keys.w = FALSE;
	else if (keycode == KEY_A || keycode == KEY_Q)
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
