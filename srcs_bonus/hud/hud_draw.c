/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:05:00 by Codex             #+#    #+#             */
/*   Updated: 2026/04/11 15:33:01 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*hud_target(t_app *app)
{
	if (app->bonus.retro.enabled && app->bonus.retro.out.addr)
		return (&app->bonus.retro.out);
	return (&app->frame);
}

void	bonus_draw_hud(t_app *app)
{
	t_img	*img;
	t_img	*weapon;

	if (!app)
		return ;
	img = hud_target(app);
	if (!img || !img->addr || img->width <= 0 || img->height <= 0)
		return ;
	bonus_draw_status_bar(app, img);
	weapon = bonus_weapon_current_frame(app);
	bonus_draw_weapon_overlay(app, img, weapon);
}
