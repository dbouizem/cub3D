/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:20:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/06 13:20:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	face_factor(t_ray ray)
{
	if (ray.side == 0 && ray.ray_dir_x > 0)
		return (BONUS_FACE_E);
	if (ray.side == 0)
		return (BONUS_FACE_W);
	if (ray.ray_dir_y > 0)
		return (BONUS_FACE_S);
	return (BONUS_FACE_N);
}

static int	quantize_chan(int c, int step)
{
	c = ((c + step / 2) / step) * step;
	if (c > 255)
		c = 255;
	return (c);
}

static double	shade_factor(t_ray ray)
{
	double	factor;
	double	levels;

	factor = 1.0 / (1.0 + ray.perp_dist * BONUS_SHADE_DIST);
	if (ray.side == 1)
		factor *= BONUS_SHADE_SIDE;
	factor *= face_factor(ray);
	factor = pow(factor, BONUS_SHADE_GAMMA);
	levels = (double)(BONUS_SHADE_LEVELS - 1);
	if (levels > 0.0)
		factor = floor(factor * levels + 0.5) / levels;
	if (factor < BONUS_SHADE_MIN)
		factor = BONUS_SHADE_MIN;
	if (factor > 1.0)
		factor = 1.0;
	return (factor);
}

static void	quantize_rgb(int *r, int *g, int *b)
{
	int	step;

	if (BONUS_PALETTE_STEPS <= 1)
		return ;
	step = 255 / (BONUS_PALETTE_STEPS - 1);
	*r = quantize_chan(*r, step);
	*g = quantize_chan(*g, step);
	*b = quantize_chan(*b, step);
}

int	apply_wall_shading(int color, t_ray ray)
{
	double	factor;
	int		r;
	int		g;
	int		b;

	factor = shade_factor(ray);
	r = (int)(((color >> 16) & 255) * factor);
	g = (int)(((color >> 8) & 255) * factor);
	b = (int)((color & 255) * factor);
	quantize_rgb(&r, &g, &b);
	return ((r << 16) | (g << 8) | b);
}
