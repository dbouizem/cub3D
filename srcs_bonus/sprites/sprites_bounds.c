/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bounds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bonus_sprite_is_opaque(unsigned int color)
{
	return (color != 0 && color != 0xFF000000);
}

static void	update_bounds(t_sprite_proj *p, int x, int y)
{
	if (x < p->tx0)
		p->tx0 = x;
	if (x > p->tx1)
		p->tx1 = x;
	if (y < p->ty0)
		p->ty0 = y;
	if (y > p->ty1)
		p->ty1 = y;
}

static void	find_visible_bounds(t_img *tex, t_sprite_proj *p)
{
	int	x;
	int	y;

	y = -1;
	while (++y < tex->height)
	{
		x = -1;
		while (++x < tex->width)
		{
			if (bonus_sprite_is_opaque(retro_get_pixel(tex, x, y)))
				update_bounds(p, x, y);
		}
	}
}

static void	set_full_bounds(t_img *tex, t_sprite_proj *p)
{
	p->tx0 = 0;
	p->tx1 = tex->width - 1;
	p->ty0 = 0;
	p->ty1 = tex->height - 1;
}

void	bonus_sprite_setup_bounds(t_img *tex, t_sprite_proj *p)
{
	if (!tex || !tex->addr || tex->width <= 0 || tex->height <= 0)
	{
		p->tx0 = 0;
		p->tx1 = 0;
		p->ty0 = 0;
		p->ty1 = 0;
		return ;
	}
	p->tx0 = tex->width;
	p->tx1 = -1;
	p->ty0 = tex->height;
	p->ty1 = -1;
	find_visible_bounds(tex, p);
	if (p->tx1 < p->tx0 || p->ty1 < p->ty0)
		set_full_bounds(tex, p);
}
