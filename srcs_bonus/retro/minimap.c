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

void	bonus_draw_minimap(t_app *app)
{
	t_mm	mm;

	if (!app || app->bonus.retro.enabled == 0
		|| !app->bonus.retro.minimap.addr)
		return ;
	mm.size = app->bonus.retro.minimap.width;
	mm.ox = app->frame.width - BONUS_MINIMAP_PAD - mm.size;
	mm.oy = app->frame.height - BONUS_MINIMAP_PAD - mm.size;
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
