/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:10:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/07 10:10:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	wall_index(char c)
{
	if (c >= '2' && c <= '9')
		return (c - '2');
	if (c >= 'a' && c <= 'z')
		return (8 + c - 'a');
	if (bonus_symbol_index(c) >= 0)
		return (0);
	return (-1);
}

static t_img	*pick_bonus_wall(t_app *app, char tile)
{
	int		idx;
	t_img	*anim;

	idx = wall_index(tile);
	if (idx < 0)
		return (NULL);
	anim = bonus_pick_anim_texture(app, tile);
	if (anim != NULL)
		return (anim);
	if (idx < 0 || idx >= BONUS_WALL_COUNT)
		return (NULL);
	if (!app->bonus_walls[idx].img_ptr || !app->bonus_walls[idx].addr)
		return (NULL);
	return (&app->bonus_walls[idx]);
}

t_img	*bonus_pick_wall_texture(t_app *app, char tile)
{
	t_img	*sym;
	t_img	*anim;

	if (tile >= 'A' && tile <= 'Z'
		&& tile != 'N' && tile != 'S' && tile != 'E' && tile != 'W')
		return (bonus_pick_door_texture(app, tile));
	if (bonus_symbol_index(tile) >= 0)
	{
		anim = bonus_pick_anim_texture(app, tile);
		if (anim != NULL)
			return (anim);
		sym = bonus_pick_symbol_texture(app, tile);
		if (sym != NULL)
			return (sym);
	}
	return (pick_bonus_wall(app, tile));
}
