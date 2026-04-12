/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_glyphs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bonus_fill_rect(t_img *img, t_rect r, int color)
{
	int	xx;
	int	yy;

	yy = 0;
	while (yy < r.h)
	{
		xx = 0;
		while (xx < r.w)
		{
			put_pixel(img, r.x + xx, r.y + yy, color);
			xx++;
		}
		yy++;
	}
}

static int	label_glyph_index(char c)
{
	char	map[16];
	int		i;

	ft_memcpy(map, "ABCEHILMOPRST:- ", 16);
	i = 0;
	while (i < 16 && map[i] != c)
		i++;
	return (i);
}

void	bonus_draw_digit(t_img *img, t_hud_text txt, int digit)
{
	static const unsigned char	glyphs[10][5] = {{7, 5, 5, 5, 7},
	{2, 6, 2, 2, 7}, {7, 1, 7, 4, 7}, {7, 1, 7, 1, 7},
	{5, 5, 7, 1, 1}, {7, 4, 7, 1, 7}, {7, 4, 7, 5, 7},
	{7, 1, 1, 1, 1}, {7, 5, 7, 5, 7}, {7, 5, 7, 1, 7}};
	int							row;
	int							col;

	if (digit < 0 || digit > 9)
		return ;
	row = -1;
	while (++row < 5)
	{
		col = -1;
		while (++col < 3)
			if ((glyphs[digit][row] >> (2 - col)) & 1)
				bonus_fill_rect(img, (t_rect){txt.x + col * txt.scale,
					txt.y + row * txt.scale, txt.scale, txt.scale},
					txt.color);
	}
}

void	bonus_draw_label_glyph(t_img *img, t_hud_text txt, char c)
{
	static const unsigned char	glyphs[16][5] = {
	{2, 5, 7, 5, 5}, {6, 5, 6, 5, 6}, {3, 4, 4, 4, 3},
	{7, 4, 6, 4, 7}, {5, 5, 7, 5, 5}, {7, 2, 2, 2, 7},
	{4, 4, 4, 4, 7}, {5, 7, 7, 5, 5}, {7, 5, 5, 5, 7},
	{6, 5, 6, 4, 4}, {6, 5, 6, 5, 5}, {7, 4, 7, 1, 7},
	{7, 2, 2, 2, 2}, {7, 4, 4, 4, 7}, {2, 0, 2, 0, 2},
	{0, 0, 0, 0, 0}};
	int							row;
	int							col;
	int							i;

	i = label_glyph_index(c);
	if (i >= 16)
		return ;
	row = -1;
	while (++row < 5)
	{
		col = -1;
		while (++col < 3)
			if ((glyphs[i][row] >> (2 - col)) & 1)
				bonus_fill_rect(img, (t_rect){txt.x + col * txt.scale,
					txt.y + row * txt.scale, txt.scale, txt.scale},
					txt.color);
	}
}
