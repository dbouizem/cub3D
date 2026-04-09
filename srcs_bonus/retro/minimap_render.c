/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 19:41:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bonus_minimap_clear(t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
			put_pixel(img, x++, y, 0);
		y++;
	}
}

static int	minimap_cell_color(t_app *app, int cell_x, int cell_y)
{
	char	c;

	c = bonus_map_cell_at(app, cell_x, cell_y);
	if (c == ' ')
		return (BONUS_MINIMAP_VOID);
	if (bonus_is_door_tile(c))
	{
		if (bonus_door_is_blocking(app, cell_x + 0.5, cell_y + 0.5))
			return (BONUS_MINIMAP_DOOR_C);
		return (BONUS_MINIMAP_DOOR_O);
	}
	if (bonus_is_solid_tile(c))
		return (BONUS_MINIMAP_WALL);
	return (BONUS_MINIMAP_FLOOR);
}

void	bonus_minimap_render_pixels(t_app *app, t_img *img, t_mm mm)
{
	int		x;
	int		y;
	int		lx;
	int		ly;
	double	scale;

	scale = BONUS_MINIMAP_TILE * app->bonus.retro.minimap_zoom;
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
		{
			lx = x - mm.cx;
			ly = y - mm.cy;
			if (lx * lx + ly * ly > mm.r2)
				continue ;
			if (lx * lx + ly * ly >= mm.ring2)
				put_pixel(img, x, y, BONUS_MINIMAP_RING);
			else
				put_pixel(img, x, y, minimap_cell_color(app,
						(int)app->player.x + (int)(lx / scale),
						(int)app->player.y + (int)(ly / scale)));
		}
	}
}

void	bonus_minimap_draw_player(t_img *img, t_mm mm)
{
	int	px;
	int	py;

	py = -2;
	while (py <= 2)
	{
		px = -2;
		while (px <= 2)
		{
			if (px * px + py * py <= 5)
				put_pixel(img, mm.cx + px + 1, mm.cy + py + 1,
					BONUS_MINIMAP_SHADOW);
			if (px * px + py * py <= 4)
				put_pixel(img, mm.cx + px, mm.cy + py, BONUS_MINIMAP_PLAYER);
			px++;
		}
		py++;
	}
}

void	bonus_minimap_blit(t_app *app, t_img *img, t_mm mm)
{
	int				x;
	int				y;
	unsigned int	color;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			color = retro_get_pixel(img, x, y);
			if (color != 0)
				put_pixel(&app->frame, mm.ox + x, mm.oy + y, (int)color);
			x++;
		}
		y++;
	}
}
