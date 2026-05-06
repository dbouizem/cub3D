/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 18:40:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bonus_minimap_clear(t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
			put_pixel(img, x++, y, 0);
		y++;
	}
}

void	bonus_minimap_draw_player(t_img *img, t_mm mm)
{
	int	px;
	int	py;

	py = -2;
	while (py <= 2)
	{
		px = -2;
		while (px <= 2)
		{
			if (px * px + py * py <= 5)
				put_pixel(img, mm.cx + px + 1, mm.cy + py + 1,
					BONUS_MINIMAP_SHADOW);
			if (px * px + py * py <= 4)
				put_pixel(img, mm.cx + px, mm.cy + py, BONUS_MINIMAP_PLAYER);
			px++;
		}
		py++;
	}
}

void	bonus_minimap_blit(t_app *app, t_img *img, t_mm mm)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			color = retro_get_pixel(img, x, y);
			if (color != 0)
				put_pixel(&app->frame, mm.ox + x, mm.oy + y, (int)color);
			x++;
		}
		y++;
	}
}

void	bonus_draw_minimap(t_app *app)
{
	t_mm	mm;

	if (!app || app->bonus.retro.enabled == 0
		|| !app->bonus.retro.minimap.addr)
		return ;
	mm.size = app->bonus.retro.minimap.width;
	mm.ox = BONUS_MINIMAP_PAD;
	mm.oy = BONUS_MINIMAP_PAD;
	mm.cx = mm.size / 2;
	mm.cy = mm.size / 2;
	mm.r2 = (mm.size / 2 - 1) * (mm.size / 2 - 1);
	mm.ring2 = (mm.size / 2 - BONUS_MINIMAP_RING_THICKNESS)
		* (mm.size / 2 - BONUS_MINIMAP_RING_THICKNESS);
	bonus_minimap_clear(&app->bonus.retro.minimap);
	bonus_minimap_render_pixels(app, &app->bonus.retro.minimap, mm);
	bonus_minimap_draw_player(&app->bonus.retro.minimap, mm);
	bonus_minimap_blit(app, &app->bonus.retro.minimap, mm);
}
