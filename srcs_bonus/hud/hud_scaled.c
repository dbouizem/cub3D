/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_scaled.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_opaque_scaled_pixel(unsigned int color)
{
	return (color != 0 && color != 0xFF000000);
}

static void	put_scaled_pixel(t_img *dst, t_rect r, int pos[2], int color)
{
	int	xx;
	int	yy;

	yy = -1;
	while (++yy < r.w)
	{
		xx = -1;
		while (++xx < r.w)
			put_pixel(dst, r.x + pos[0] * r.w + xx,
				r.y + pos[1] * r.w + yy, color);
	}
}

void	bonus_blit_scaled(t_img *dst, t_img *src, t_rect r)
{
	int				pos[2];
	unsigned int	color;

	if (!dst || !src || !src->addr || r.w <= 0)
		return ;
	pos[1] = -1;
	while (++pos[1] < src->height)
	{
		pos[0] = -1;
		while (++pos[0] < src->width)
		{
			color = retro_get_pixel(src, pos[0], pos[1]);
			if (is_opaque_scaled_pixel(color))
				put_scaled_pixel(dst, r, pos, (int)color);
		}
	}
}
