/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	mix_channel(int a, int b, int t)
{
	return (a + ((b - a) * t) / 255);
}

static int	mix_color(int a, int b, int t)
{
	int	ar;
	int	ag;
	int	ab;

	ar = (a >> 16) & 0xFF;
	ag = (a >> 8) & 0xFF;
	ab = a & 0xFF;
	return ((mix_channel(ar, (b >> 16) & 0xFF, t) << 16)
		| (mix_channel(ag, (b >> 8) & 0xFF, t) << 8)
		| mix_channel(ab, b & 0xFF, t));
}

static int	hud_noise(int x, int y)
{
	int	n;

	n = x * 37 + y * 57 + x * y * 13;
	n ^= n >> 3;
	n ^= n << 5;
	if (n < 0)
		n = -n;
	return (n & 31);
}

void	bonus_draw_hud_texture(t_img *img, t_rect r)
{
	int		xx;
	int		yy;
	int		color;
	int		tint;

	yy = -1;
	while (++yy < r.h)
	{
		xx = -1;
		while (++xx < r.w)
		{
			color = mix_color(0x003A3A3D, 0x00262629, (yy * 255) / r.h);
			tint = hud_noise(r.x + xx, r.y + yy);
			color = mix_color(color, 0x00454549, tint * 4);
			if (((xx + r.x) / 18 + (yy + r.y) / 12) % 2 == 0)
				color = mix_color(color, 0x00515156, 16);
			put_pixel(img, r.x + xx, r.y + yy, color);
		}
	}
}

void	bonus_draw_rivet(t_img *img, int x, int y)
{
	bonus_fill_rect(img, (t_rect){x, y, 4, 4}, 0x00141416);
	bonus_fill_rect(img, (t_rect){x + 1, y + 1, 2, 2}, 0x007A7A7E);
}
