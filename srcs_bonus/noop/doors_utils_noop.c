/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils_noop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 16:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 16:55:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bonus_is_door_tile(char c)
{
	(void)c;
	return (0);
}

char	bonus_map_cell_at(t_app *app, int x, int y)
{
	int	len;

	if (!app || !app->map.grid || y < 0 || y >= app->map.height)
		return (' ');
	len = (int)ft_strlen(app->map.grid[y]);
	if (x < 0 || x >= len)
		return (' ');
	return (app->map.grid[y][x]);
}
