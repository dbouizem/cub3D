/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_weapon_slot.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bonus_draw_weapon_slot(t_img *img, t_rect r)
{
	bonus_draw_panel_frame(img, r);
	bonus_fill_rect(img, (t_rect){r.x + 6, r.y + 6, r.w - 12, r.h - 12},
		0x00161618);
	bonus_fill_rect(img, (t_rect){r.x + 14, r.y + 14, r.w - 28, r.h - 28},
		0x00202023);
}
