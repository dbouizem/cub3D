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
	if (ft_strchr(BONUS_WALL_SYMBOL_SET, c) != NULL)
		return (1);
	return ((c >= '2' && c <= '9') || (c >= 'a' && c <= 'z'));
}

static int	is_bonus_door(char c)
{
	if (c < 'A' || c > 'Z')
		return (0);
	return (c != 'N' && c != 'S' && c != 'E' && c != 'W');
}

int	bonus_is_valid_map_char(char c)
{
	return (is_bonus_wall(c) || is_bonus_door(c));
}

int	bonus_is_solid_tile(char c)
{
	return (c == '1' || is_bonus_wall(c) || is_bonus_door(c));
}
