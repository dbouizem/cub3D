/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_pixels.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	minimap_put_cell(t_app *app, t_img *img, t_mm mm, int pos[2])
{
	int		lx;
	int		ly;
	double	scale;

	lx = pos[0] - mm.cx;
	ly = pos[1] - mm.cy;
	if (lx * lx + ly * ly > mm.r2)
		return ;
	if (lx * lx + ly * ly >= mm.ring2)
		put_pixel(img, pos[0], pos[1], BONUS_MINIMAP_RING);
	else
	{
		scale = BONUS_MINIMAP_TILE * app->bonus.retro.minimap_zoom;
		put_pixel(img, pos[0], pos[1], minimap_cell_color(app,
				(int)app->player.x + (int)floor((double)lx / scale),
				(int)app->player.y + (int)floor((double)ly / scale)));
	}
}

void	bonus_minimap_render_pixels(t_app *app, t_img *img, t_mm mm)
{
	int	pos[2];

	pos[1] = -1;
	while (++pos[1] < img->height)
	{
		pos[0] = -1;
		while (++pos[0] < img->width)
			minimap_put_cell(app, img, mm, pos);
	}
}
