/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_blit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_opaque_hud_pixel(unsigned int color)
{
	return (color != 0 && color != 0xFF000000);
}

static void	update_hud_bounds(int bounds[4], int x, int y)
{
	if (x < bounds[0])
		bounds[0] = x;
	if (y < bounds[1])
		bounds[1] = y;
	if (x > bounds[2])
		bounds[2] = x;
	if (y > bounds[3])
		bounds[3] = y;
}

void	bonus_find_visible_hud_bounds(t_img *img, int bounds[4])
{
	int	x;
	int	y;

	bounds[0] = img->width;
	bounds[1] = img->height;
	bounds[2] = -1;
	bounds[3] = -1;
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			if (is_opaque_hud_pixel(retro_get_pixel(img, x, y)))
				update_hud_bounds(bounds, x, y);
	}
	if (bounds[2] < bounds[0] || bounds[3] < bounds[1])
	{
		bounds[0] = 0;
		bounds[1] = 0;
		bounds[2] = img->width - 1;
		bounds[3] = img->height - 1;
	}
}

void	bonus_blit_masked_bounds(t_img *dst, t_img *src, t_rect r,
	int bounds[4])
{
	int				x;
	int				y;
	unsigned int	color;

	y = bounds[1];
	while (y <= bounds[3])
	{
		x = bounds[0];
		while (x <= bounds[2])
		{
			color = retro_get_pixel(src, x, y);
			if (is_opaque_hud_pixel(color))
				put_pixel(dst, r.x + x - bounds[0], r.y + y - bounds[1],
					(int)color);
			x++;
		}
		y++;
	}
}
