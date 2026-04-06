/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upscale.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/06 11:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	can_upscale(t_app *app)
{
	if (!app || !app->bonus_fb.addr || !app->bonus_out.addr)
		return (0);
	if (app->bonus_fb.width <= 0 || app->bonus_fb.height <= 0)
		return (0);
	if (app->bonus_out.width <= 0 || app->bonus_out.height <= 0)
		return (0);
	if (app->bonus_fb.bpp < 8 || app->bonus_out.bpp < 8)
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
	while (y < app->bonus_out.height)
	{
		src_y = y * app->bonus_fb.height / app->bonus_out.height;
		x = 0;
		while (x < app->bonus_out.width)
		{
			src_x = x * app->bonus_fb.width / app->bonus_out.width;
			color = retro_get_pixel(&app->bonus_fb, src_x, src_y);
			put_pixel(&app->bonus_out, x, y, (int)color);
			x++;
		}
		y++;
	}
}
