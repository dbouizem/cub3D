/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_overlay.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bonus_draw_weapon_overlay(t_app *app, t_img *dst, t_img *src)
{
	int		bounds[4];
	t_rect	r;

	if (!app || !dst || !src || !src->addr)
		return ;
	bonus_find_visible_hud_bounds(src, bounds);
	r.w = bounds[2] - bounds[0] + 1;
	r.h = bounds[3] - bounds[1] + 1;
	r.x = dst->width / 2 - r.w / 2;
	r.y = dst->height - BONUS_HUD_BAR_H - r.h - 1;
	if (r.x < 0)
		r.x = 0;
	if (r.y < 0)
		r.y = 0;
	bonus_blit_masked_bounds(dst, src, r, bounds);
}
