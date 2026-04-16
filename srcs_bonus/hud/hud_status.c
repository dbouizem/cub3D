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

static const char	*g_hud_labels[4] = {"AMMO", "HP", "ARMOR", "SCORE"};
static const int	g_hud_colors[4] = {0x00D9B44A, 0x00D94A4A,
	0x004AA3D9, 0x00F0D35A};

static void	draw_box_digits(t_img *img, t_rect r, int value, int digits)
{
	int	x;

	x = r.x + r.w / 2 - bonus_number_width(digits, 5) / 2;
	bonus_draw_number(img, (t_hud_text){x, r.y + 18, 0x00B00000, 5},
		value, digits);
	bonus_draw_number(img, (t_hud_text){x - 2, r.y + 16, 0x00FF1E1E, 5},
		value, digits);
}

static void	draw_stat_box(t_img *img, t_rect r, const char *label, int value)
{
	int	digits;

	digits = 3;
	if (ft_strcmp(label, "SCORE") == 0)
		digits = 4;
	bonus_draw_panel_frame(img, r);
	bonus_fill_rect(img, (t_rect){r.x + 8, r.y + 8, r.w - 16, r.h - 16},
		0x0018181A);
	draw_box_digits(img, r, value, digits);
	bonus_draw_label(img, (t_hud_text){r.x + r.w / 2
		- bonus_label_width(label, 2) / 2, r.y + r.h - 22,
		0x00A0A0A4, 2}, label);
}

static void	draw_stat_table(t_app *app, t_img *img, t_rect r)
{
	int	row_h;
	int	i;
	int	num_x;

	bonus_draw_panel_frame(img, r);
	bonus_fill_rect(img, (t_rect){r.x + 7, r.y + 7, r.w - 14, r.h - 14},
		0x0018181A);
	row_h = (r.h - 20) / 4;
	i = -1;
	while (++i < 4)
	{
		bonus_draw_label(img, (t_hud_text){r.x + 14, r.y + 13 + row_h * i,
			g_hud_colors[i], 2}, g_hud_labels[i]);
		num_x = r.x + r.w - 16 - bonus_number_width(3 + (i == 3), 2);
		bonus_draw_number(img, (t_hud_text){num_x, r.y + 13 + row_h * i,
			0x00F7E75D, 2}, (i == 0) * app->bonus.stats.ammo
			+ (i == 1) * app->bonus.stats.hp + (i == 2)
			* app->bonus.stats.armor + (i == 3) * app->bonus.stats.score,
			3 + (i == 3));
	}
}

static void	draw_right_hud(t_app *app, t_img *img, int bar_y)
{
	int	table_x;
	int	score_x;
	int	armor_x;

	table_x = img->width - 10 - 188;
	score_x = table_x - 10 - 96;
	armor_x = score_x - 10 - 96;
	draw_stat_box(img, (t_rect){armor_x, bar_y + 8, 96,
		BONUS_HUD_BAR_H - 16}, "ARMOR", app->bonus.stats.armor);
	draw_stat_box(img, (t_rect){score_x, bar_y + 8, 96,
		BONUS_HUD_BAR_H - 16}, "SCORE", app->bonus.stats.score);
	draw_stat_table(app, img, (t_rect){table_x, bar_y + 8, 188,
		BONUS_HUD_BAR_H - 16});
}

void	bonus_draw_status_bar(t_app *app, t_img *img)
{
	int	bar_y;
	int	face_x;

	bar_y = img->height - BONUS_HUD_BAR_H;
	face_x = img->width / 2 - 108 / 2;
	bonus_draw_hud_backplate(img, bar_y, BONUS_HUD_BAR_H);
	bonus_fill_rect(img, (t_rect){face_x - 6, bar_y + 6, 120,
		BONUS_HUD_BAR_H - 12}, 0x00111113);
	bonus_draw_face_panel(app, img, (t_rect){face_x, bar_y + 4, 108,
		BONUS_HUD_BAR_H - 8});
	bonus_draw_weapon_slot(img, (t_rect){face_x - 38, bar_y + 10, 32, 56});
	bonus_draw_weapon_slot(img, (t_rect){face_x + 114, bar_y + 10, 32, 56});
	draw_stat_box(img, (t_rect){10, bar_y + 8, 96, BONUS_HUD_BAR_H - 16},
		"AMMO", app->bonus.stats.ammo);
	draw_stat_box(img, (t_rect){116, bar_y + 8, 96, BONUS_HUD_BAR_H - 16},
		"HP", app->bonus.stats.hp);
	draw_right_hud(app, img, bar_y);
}
