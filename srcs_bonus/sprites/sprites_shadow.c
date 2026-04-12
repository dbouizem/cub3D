/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_shadow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	darken_color(int color, double factor)
{
	int	r;
	int	g;
	int	b;

	r = (int)(((color >> 16) & 255) * factor);
	g = (int)(((color >> 8) & 255) * factor);
	b = (int)((color & 255) * factor);
	return ((r << 16) | (g << 8) | b);
}

static void	draw_shadow_pixel(t_app *app, t_sprite_proj p, int x, int y)
{
	int	color;

	if (x < 0 || x >= app->frame.width || y < 0 || y >= app->frame.height)
		return ;
	if (x >= app->bonus.sprites.zcap || p.sy >= app->bonus.sprites.zbuf[x])
		return ;
	color = (int)retro_get_pixel(&app->frame, x, y);
	put_pixel(&app->frame, x, y, darken_color(color,
			BONUS_SPRITE_SHADOW_DARKEN));
}

static void	shadow_radii(t_sprite_proj p, int *rx, int *ry)
{
	*rx = (int)(p.sw * BONUS_SPRITE_SHADOW_W * 0.5);
	*ry = (int)(p.sh * BONUS_SPRITE_SHADOW_H * 0.5);
	if (*rx < 2)
		*rx = 2;
	if (*ry < 1)
		*ry = 1;
}

static void	draw_shadow_row(t_app *app, t_sprite_proj p, int y, int rx)
{
	double	nx;
	double	ny;
	int		x;
	int		ry;

	ry = (int)(p.sh * BONUS_SPRITE_SHADOW_H * 0.5);
	if (ry < 1)
		ry = 1;
	x = p.sx - rx;
	while (x <= p.sx + rx)
	{
		nx = (double)(x - p.sx) / (double)rx;
		ny = (double)(y - p.y1) / (double)ry;
		if (nx * nx + ny * ny <= 1.0 && ((x + y) & 1) == 0)
			draw_shadow_pixel(app, p, x, y);
		x++;
	}
}

void	bonus_draw_sprite_shadow(t_app *app, t_sprite_proj p)
{
	int	xrad;
	int	yrad;
	int	y;

	shadow_radii(p, &xrad, &yrad);
	y = p.y1 - yrad;
	while (y <= p.y1 + yrad)
	{
		draw_shadow_row(app, p, y, xrad);
		y++;
	}
}
