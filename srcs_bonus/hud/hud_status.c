/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/05/07 11:25:47 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_stat_meta(const char **labels, int *colors)
{
	labels[0] = "AMMO";
	labels[1] = "HP";
	labels[2] = "ARMOR";
	labels[3] = "SCORE";
	colors[0] = 0x00D9B44A;
	colors[1] = 0x00D94A4A;
	colors[2] = 0x004AA3D9;
	colors[3] = 0x00F0D35A;
}

static void	draw_stat_box(t_img *img, t_rect r, const char *label, int value)
{
	int	digits;
	int	x;

	digits = 3;
	if (ft_strcmp(label, "SCORE") == 0)
		digits = 4;
	bonus_draw_panel_frame(img, r);
	bonus_fill_rect(img, (t_rect){r.x + 8, r.y + 8, r.w - 16, r.h - 16},
		0x0018181A);
	x = r.x + r.w / 2 - bonus_number_width(digits, 5) / 2;
	bonus_draw_number(img, (t_hud_text){x, r.y + 18, 0x00B00000, 5},
		value, digits);
	bonus_draw_number(img, (t_hud_text){x - 2, r.y + 16, 0x00FF1E1E, 5},
		value, digits);
	bonus_draw_label(img, (t_hud_text){r.x + r.w / 2
		- bonus_label_width(label, 2) / 2, r.y + r.h - 22,
		0x00A0A0A4, 2}, label);
}

static void	draw_stat_table(t_app *app, t_img *img, t_rect r)
{
	int			row_h;
	int			i;
	int			num_x;
	const char	*labels[4];
	int			colors[4];

	init_stat_meta(labels, colors);
	bonus_draw_panel_frame(img, r);
	bonus_fill_rect(img, (t_rect){r.x + 7, r.y + 7, r.w - 14, r.h - 14},
		0x0018181A);
	row_h = (r.h - 20) / 4;
	i = -1;
	while (++i < 4)
	{
		bonus_draw_label(img, (t_hud_text){r.x + 14, r.y + 13 + row_h * i,
			colors[i], 2}, labels[i]);
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
	int	center_end;

	table_x = img->width - 40 - 188;
	score_x = table_x - 40 - 96;
	armor_x = score_x - 10 - 96;
	center_end = img->width / 2 + 92;
	if (armor_x < center_end + 12)
	{
		score_x = img->width - 40 - 96;
		armor_x = score_x - 10 - 96;
		draw_stat_box(img, (t_rect){armor_x, bar_y + 8, 96,
			BONUS_HUD_BAR_H - 16}, "ARMOR", app->bonus.stats.armor);
		draw_stat_box(img, (t_rect){score_x, bar_y + 8, 96,
			BONUS_HUD_BAR_H - 16}, "SCORE", app->bonus.stats.score);
		return ;
	}
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
	bonus_draw_left_hud(app, img, bar_y, face_x);
	draw_right_hud(app, img, bar_y);
}
