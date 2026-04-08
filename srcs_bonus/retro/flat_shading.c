/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flat_shading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/07 12:40:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	quantize_chan(int c, int step)
{
	c = ((c + step / 2) / step) * step;
	if (c > 255)
		c = 255;
	return (c);
}

static double	flat_factor_at_y(int y, int height)
{
	double	mid;
	double	t;
	double	factor;
	double	denom;

	if (height <= 1)
		return (1.0);
	mid = (double)height * 0.5;
	if ((double)y < mid)
	{
		t = (double)y / mid;
		factor = BONUS_FLAT_CEIL_TOP * (1.0 - t) + BONUS_FLAT_HORIZON * t;
	}
	else
	{
		denom = (double)(height - 1) - mid;
		if (denom <= 0.0)
			denom = 1.0;
		t = ((double)y - mid) / denom;
		factor = BONUS_FLAT_HORIZON * (1.0 - t)
			+ BONUS_FLAT_FLOOR_BOTTOM * t;
	}
	factor = pow(factor, BONUS_FLAT_GAMMA);
	return (factor);
}

int	apply_flat_shading(int color, int y, int height)
{
	double	factor;
	int		r;
	int		g;
	int		b;

	factor = flat_factor_at_y(y, height);
	r = (int)(((color >> 16) & 255) * factor);
	g = (int)(((color >> 8) & 255) * factor);
	b = (int)((color & 255) * factor);
	r = quantize_chan(r, 1);
	g = quantize_chan(g, 1);
	b = quantize_chan(b, 1);
	return ((r << 16) | (g << 8) | b);
}
