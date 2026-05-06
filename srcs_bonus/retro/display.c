/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/05/06 17:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bonus_apply_resolution_preset(t_app *app, int keycode)
{
	if (keycode == KEY_F1)
		return (resize_window(app, 960, 540, 1));
	if (keycode == KEY_F2)
		return (resize_window(app, 1280, 720, 1));
	if (keycode == KEY_F3)
		return (resize_window(app, 1600, 900, 1));
	return (0);
}

static int	can_upscale(t_app *app)
{
	if (!app || !app->bonus.retro.fb.addr || !app->bonus.retro.out.addr)
		return (0);
	if (app->bonus.retro.fb.width <= 0 || app->bonus.retro.fb.height <= 0)
		return (0);
	if (app->bonus.retro.out.width <= 0 || app->bonus.retro.out.height <= 0)
		return (0);
	if (app->bonus.retro.fb.bpp < 8 || app->bonus.retro.out.bpp < 8)
		return (0);
	return (1);
}

void	retro_upscale_to_out(t_app *app)
{
	int				x;
	int				y;
	int				src_x;
	int				src_y;
	unsigned int	color;

	if (!can_upscale(app))
		return ;
	y = 0;
	while (y < app->bonus.retro.out.height)
	{
		src_y = y * app->bonus.retro.fb.height / app->bonus.retro.out.height;
		x = 0;
		while (x < app->bonus.retro.out.width)
		{
			src_x = x * app->bonus.retro.fb.width
				/ app->bonus.retro.out.width;
			color = retro_get_pixel(&app->bonus.retro.fb, src_x, src_y);
			put_pixel(&app->bonus.retro.out, x, y, (int)color);
			x++;
		}
		y++;
	}
}
