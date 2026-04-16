/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_level.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 00:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/17 01:09:33 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	current_level(t_app *app)
{
	int	level;

	level = 1;
	if (app->bonus.levels.active)
		level = app->bonus.levels.current + 1;
	if (level < 1)
		level = 1;
	if (level > BONUS_LEVEL_MAX)
		level = BONUS_LEVEL_MAX;
	return (level);
}

static void	draw_level_cell(t_img *img, t_rect r, int level, int current)
{
	int	color;
	int	text;
	int	x;

	color = 0x00222225;
	text = 0x005A5A5E;
	if (level == current)
	{
		color = 0x006A5A1E;
		text = 0x00F7E75D;
	}
	bonus_fill_rect(img, r, color);
	bonus_fill_rect(img, (t_rect){r.x, r.y, r.w, 1}, 0x0069696D);
	bonus_fill_rect(img, (t_rect){r.x, r.y, 1, r.h}, 0x0069696D);
	bonus_fill_rect(img, (t_rect){r.x, r.y + r.h - 1, r.w, 1}, 0x00111113);
	bonus_fill_rect(img, (t_rect){r.x + r.w - 1, r.y, 1, r.h}, 0x00111113);
	x = r.x + r.w / 2 - bonus_number_width(1, 2) / 2;
	bonus_draw_number(img, (t_hud_text){x, r.y + 4, 0x00101010, 2}, level, 1);
	bonus_draw_number(img, (t_hud_text){x, r.y + 3, text, 2}, level, 1);
}

static void	draw_level_rows(t_img *img, t_rect r, int current)
{
	t_rect	cell;
	int		row;
	int		col;
	int		level;

	cell.w = 24;
	cell.h = 18;
	row = 0;
	level = 1;
	while (row < 2)
	{
		col = 0;
		while (col < 4)
		{
			cell.x = r.x + 39 + col * 27;
			cell.y = r.y + 10 + row * 22;
			draw_level_cell(img, cell, level++, current);
			col++;
		}
		row++;
	}
}

void	bonus_draw_level_box(t_app *app, t_img *img, t_rect r)
{
	bonus_draw_panel_frame(img, r);
	bonus_fill_rect(img, (t_rect){r.x + 8, r.y + 8, r.w - 16, r.h - 16},
		0x0018181A);
	draw_level_rows(img, r, current_level(app));
	bonus_draw_label(img, (t_hud_text){r.x + r.w / 2
		- bonus_label_width("LEVELS", 2) / 2, r.y + r.h - 21,
		0x00A0A0A4, 2}, "LEVELS");
}

void	bonus_draw_left_hud(t_app *app, t_img *img, int bar_y, int face_x)
{
	int	level_x;
	int	slot_x;
	int	left_x;
	int	hp_x;

	left_x = 40;
	slot_x = face_x - 38;
	hp_x = left_x + 96 + 10;
	level_x = hp_x + 96 + 40;
	bonus_draw_mid_stat_box(img, (t_rect){left_x, bar_y + 8, 96,
		BONUS_HUD_BAR_H - 16}, "AMMO");
	bonus_draw_big_stat(img, left_x + 48 - bonus_number_width(3, 6) / 2,
		bar_y + 24, app->bonus.stats.ammo);
	bonus_draw_mid_stat_box(img, (t_rect){hp_x, bar_y + 8, 96,
		BONUS_HUD_BAR_H - 16}, "HP");
	bonus_draw_big_stat(img, hp_x + 48 - bonus_number_width(3, 6) / 2,
		bar_y + 24, app->bonus.stats.hp);
	if (level_x + 188 <= slot_x - 36)
		bonus_draw_level_box(app, img, (t_rect){level_x, bar_y + 8, 188,
			BONUS_HUD_BAR_H - 16});
}
