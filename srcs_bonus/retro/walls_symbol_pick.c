/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_symbol_pick.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 08:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/08 08:40:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bonus_symbol_index(char c)
{
	const char	*set;
	int			i;

	set = BONUS_WALL_SYMBOL_SET;
	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

t_img	*bonus_pick_symbol_texture(t_app *app, char tile)
{
	int	idx;

	idx = bonus_symbol_index(tile);
	if (idx < 0 || idx >= BONUS_WALL_SYMBOL_COUNT)
		return (NULL);
	if (!app->bonus_wall_symbols[idx].img_ptr
		|| !app->bonus_wall_symbols[idx].addr)
		return (NULL);
	return (&app->bonus_wall_symbols[idx]);
}
