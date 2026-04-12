/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_vignette.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:20:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 18:20:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	get_frame_pixel(t_img *img, int x, int y)
{
	char	*src;

	if (img == NULL || img->addr == NULL)
		return (0);
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0);
	src = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)src);
}

static int	mul_color(int color, double factor)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color >> 16) & 255) * factor);
	g = (int)(((color >> 8) & 255) * factor);
	b = (int)((color & 255) * factor);
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return ((r << 16) | (g << 8) | b);
}

static double	vignette_factor(t_app *app, int x, int y)
{
	double	nx;
	double	ny;
	double	dist;

	nx = ((double)x / (double)(app->frame.width - 1)) * 2.0 - 1.0;
	ny = ((double)y / (double)(app->frame.height - 1)) * 2.0 - 1.0;
	dist = sqrt(nx * nx + ny * ny) / 1.41421356237;
	if (dist <= 0.0)
		return (1.0);
	return (1.0 - BONUS_VIGNETTE_STRENGTH
		* pow(dist, BONUS_VIGNETTE_POWER));
}

void	apply_world_vignette(t_app *app)
{
	int		x;
	int		y;
	double	factor;

	if (!app || !app->frame.addr || app->frame.width <= 1
		|| app->frame.height <= 1)
		return ;
	y = -1;
	while (++y < app->frame.height)
	{
		x = -1;
		while (++x < app->frame.width)
		{
			factor = vignette_factor(app, x, y);
			if (factor < 0.999)
				put_pixel(&app->frame, x, y,
					mul_color((int)get_frame_pixel(&app->frame, x, y),
						factor));
		}
	}
}
