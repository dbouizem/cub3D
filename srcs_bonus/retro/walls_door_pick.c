/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_door_pick.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 08:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/08 08:55:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	door_index(char c)
{
	const char	*set;
	int			i;

	set = BONUS_DOOR_SET;
	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

t_img	*bonus_pick_door_texture(t_app *app, char tile)
{
	int	idx;

	idx = door_index(tile);
	if (idx < 0 || idx >= BONUS_DOOR_COUNT)
		return (NULL);
	if (!app->bonus_doors[idx].img_ptr || !app->bonus_doors[idx].addr)
		return (NULL);
	return (&app->bonus_doors[idx]);
}
