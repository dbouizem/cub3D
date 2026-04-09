/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution_preset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:05:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 14:05:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	apply_resolution_preset(t_app *app, int keycode)
{
	if (keycode == KEY_F1)
		return (resize_window(app, 960, 540, 1));
	if (keycode == KEY_F2)
		return (resize_window(app, 1280, 720, 1));
	if (keycode == KEY_F3)
		return (resize_window(app, 1600, 900, 1));
	return (0);
}
