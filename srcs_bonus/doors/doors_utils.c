/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 16:30:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 16:30:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bonus_is_door_tile(char c)
{
	return (ft_strchr(BONUS_DOOR_SET, c) != NULL);
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

t_door	*bonus_find_door(t_app *app, int x, int y)
{
	int	i;

	i = 0;
	while (i < app->bonus.doors.count)
	{
		if (app->bonus.doors.items[i].x == x
			&& app->bonus.doors.items[i].y == y)
			return (&app->bonus.doors.items[i]);
		i++;
	}
	return (NULL);
}

int	bonus_find_front_door(t_app *app, int *x, int *y)
{
	double	dist;

	dist = 0.25;
	while (dist <= BONUS_DOOR_INTERACT_DIST)
	{
		*x = (int)floor(app->player.x + app->dir_x * dist);
		*y = (int)floor(app->player.y + app->dir_y * dist);
		if (bonus_is_door_tile(bonus_map_cell_at(app, *x, *y)))
			return (1);
		dist += BONUS_DOOR_SCAN_STEP;
	}
	return (0);
}

void	bonus_toggle_door_state(t_door *door)
{
	if (door->state == DOOR_CLOSED || door->state == DOOR_CLOSING)
		door->state = DOOR_OPENING;
	else
		door->state = DOOR_CLOSING;
	door->state_timer = 0.0;
}
