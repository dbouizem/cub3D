/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_panels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bonus_draw_panel_frame(t_img *img, t_rect r)
{
	bonus_fill_rect(img, r, 0x00303033);
	bonus_fill_rect(img, (t_rect){r.x + 2, r.y + 2, r.w - 4, r.h - 4},
		0x00444447);
	bonus_fill_rect(img, (t_rect){r.x + 4, r.y + 4, r.w - 8, r.h - 8},
		0x00252528);
	bonus_fill_rect(img, (t_rect){r.x, r.y, r.w, 2}, 0x0066666A);
	bonus_fill_rect(img, (t_rect){r.x, r.y, 2, r.h}, 0x0066666A);
	bonus_fill_rect(img, (t_rect){r.x, r.y + r.h - 2, r.w, 2},
		0x00131315);
	bonus_fill_rect(img, (t_rect){r.x + r.w - 2, r.y, 2, r.h},
		0x00131315);
}

void	bonus_draw_hud_backplate(t_img *img, int y, int h)
{
	int	x;

	bonus_draw_hud_texture(img, (t_rect){0, y, img->width, h});
	bonus_fill_rect(img, (t_rect){0, y, img->width, 3}, 0x00757579);
	bonus_fill_rect(img, (t_rect){0, y + h - 4, img->width, 4}, 0x00101012);
	x = 16;
	while (x < img->width - 16)
	{
		bonus_draw_rivet(img, x, y + 10);
		bonus_draw_rivet(img, x, y + h - 14);
		x += 42;
	}
}

void	bonus_draw_big_stat(t_img *img, int x, int y, int value)
{
	bonus_draw_number(img, (t_hud_text){x, y, 0x00B00000, 6}, value, 3);
	bonus_draw_number(img, (t_hud_text){x - 2, y - 2, 0x00FF1E1E, 6},
		value, 3);
}

void	bonus_draw_mid_stat_box(t_img *img, t_rect r, const char *label)
{
	bonus_draw_panel_frame(img, r);
	bonus_fill_rect(img, (t_rect){r.x + 8, r.y + 8, r.w - 16, r.h - 16},
		0x0018181A);
	bonus_draw_label(img, (t_hud_text){r.x + r.w / 2
		- bonus_label_width(label, 2) / 2, r.y + r.h - 22,
		0x00A0A0A4, 2}, label);
}

void	bonus_draw_face_panel(t_app *app, t_img *img, t_rect r)
{
	t_img	*face;
	t_rect	src;

	bonus_draw_panel_frame(img, r);
	bonus_fill_rect(img, (t_rect){r.x + 12, r.y + 10, r.w - 24, r.h - 20},
		0x0019191B);
	face = bonus_face_current_frame(app);
	src.w = 2;
	src.h = 0;
	src.x = r.x + r.w / 2 - (face->width * src.w) / 2;
	src.y = r.y + r.h - 15 - face->height * src.w;
	bonus_blit_scaled(img, face, src);
}
