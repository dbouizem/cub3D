/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_stat_column(t_img *img, t_rect r, const char *label, int value)
{
	int	nx;

	bonus_draw_panel_frame(img, r);
	bonus_fill_rect(img, (t_rect){r.x + 7, r.y + 7, r.w - 14, r.h - 14},
		0x0018181A);
	nx = r.x + r.w / 2 - bonus_number_width(3, 6) / 2;
	bonus_draw_big_stat(img, nx, r.y + 10, value);
	bonus_draw_label(img, (t_hud_text){r.x + r.w / 2
		- bonus_label_width(label, 2) / 2, r.y + r.h - 22,
		0x00A0A0A4, 2}, label);
}

static void	draw_stat_row(t_app *app, t_img *img, t_rect r, int row)
{
	int	row_h;
	int	num_x;

	row_h = (r.h - 16) / 4;
	num_x = r.x + r.w - 14 - bonus_number_width(3, 3);
	if (row == 0)
		bonus_draw_label(img, (t_hud_text){r.x + 16, r.y + 14,
			0x00D9B44A, 2}, "AMMO");
	if (row == 0)
		bonus_draw_number(img, (t_hud_text){num_x, r.y + 12,
			0x00F7E75D, 3}, app->bonus.stats.ammo, 3);
	if (row == 1)
		bonus_draw_label(img, (t_hud_text){r.x + 16, r.y + 14 + row_h,
			0x00D94A4A, 2}, "HP");
	if (row == 1)
		bonus_draw_number(img, (t_hud_text){num_x, r.y + 12 + row_h,
			0x00F7E75D, 3}, app->bonus.stats.hp, 3);
}

static void	draw_more_stat_rows(t_app *app, t_img *img, t_rect r)
{
	int	row_h;
	int	num_x;
	int	score_x;

	row_h = (r.h - 16) / 4;
	num_x = r.x + r.w - 14 - bonus_number_width(3, 3);
	score_x = r.x + r.w - 14 - bonus_number_width(4, 3);
	bonus_draw_label(img, (t_hud_text){r.x + 16, r.y + 14 + row_h * 2,
		0x004AA3D9, 2}, "ARMOR");
	bonus_draw_number(img, (t_hud_text){num_x, r.y + 12 + row_h * 2,
		0x00F7E75D, 3}, app->bonus.stats.armor, 3);
	bonus_draw_label(img, (t_hud_text){r.x + 16, r.y + 14 + row_h * 3,
		0x00F0D35A, 2}, "SCORE");
	bonus_draw_number(img, (t_hud_text){score_x, r.y + 12 + row_h * 3,
		0x00F7E75D, 3}, app->bonus.stats.score, 4);
}

static void	draw_stat_table(t_app *app, t_img *img, t_rect r)
{
	bonus_draw_panel_frame(img, r);
	bonus_fill_rect(img, (t_rect){r.x + 7, r.y + 7, r.w - 14, r.h - 14},
		0x0018181A);
	draw_stat_row(app, img, r, 0);
	draw_stat_row(app, img, r, 1);
	draw_more_stat_rows(app, img, r);
}

void	bonus_draw_status_bar(t_app *app, t_img *img)
{
	int	bar_y;
	int	face_x;

	bar_y = img->height - BONUS_HUD_BAR_H;
	face_x = img->width / 2 - 108 / 2;
	bonus_draw_hud_backplate(img, bar_y, BONUS_HUD_BAR_H);
	draw_stat_column(img, (t_rect){10, bar_y + 8, 104, BONUS_HUD_BAR_H - 16},
		"AMMO", app->bonus.stats.ammo);
	draw_stat_column(img, (t_rect){120, bar_y + 8, 104, BONUS_HUD_BAR_H - 16},
		"HP", app->bonus.stats.hp);
	bonus_fill_rect(img, (t_rect){face_x - 6, bar_y + 6, 120,
		BONUS_HUD_BAR_H - 12}, 0x00111113);
	bonus_draw_face_panel(app, img, (t_rect){face_x, bar_y + 4, 108,
		BONUS_HUD_BAR_H - 8});
	bonus_draw_weapon_slot(img, (t_rect){face_x - 38, bar_y + 10, 32, 56});
	bonus_draw_weapon_slot(img, (t_rect){face_x + 114, bar_y + 10, 32, 56});
	bonus_draw_mid_stat_box(img, (t_rect){img->width - 384, bar_y + 8, 96,
		BONUS_HUD_BAR_H - 16}, "ARMOR");
	bonus_draw_big_stat(img, img->width - 360, bar_y + 18,
		app->bonus.stats.armor);
	draw_stat_table(app, img, (t_rect){img->width - 198, bar_y + 8, 188,
		BONUS_HUD_BAR_H - 16});
}
