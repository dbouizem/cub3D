/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_rules.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:10:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/07 10:10:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_bonus_wall(char c)
{
	if (bonus_is_sprite_tile(c))
		return (0);
	if (ft_strchr(BONUS_WALL_SYMBOL_SET, c) != NULL)
		return (1);
	return ((c >= '2' && c <= '9') || (c >= 'a' && c <= 'z'));
}

static int	is_bonus_door(char c)
{
	return (ft_strchr(BONUS_DOOR_SET, c) != NULL);
}

static int	is_bonus_player(char c)
{
	return (ft_strchr(BONUS_PLAYER_SET, c) != NULL);
}

int	bonus_is_valid_map_char(char c)
{
	return (is_bonus_wall(c) || is_bonus_door(c)
		|| is_bonus_player(c) || bonus_is_sprite_tile(c));
}

int	bonus_is_solid_tile(char c)
{
	return (c == '1' || is_bonus_wall(c) || is_bonus_door(c));
}
