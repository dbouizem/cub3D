/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickups_api.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 18:20:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/10 18:20:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_map_pickups(t_app *app)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < app->map.height)
	{
		x = 0;
		while (app->map.grid[y][x])
		{
			if (bonus_is_sprite_tile(app->map.grid[y][x]))
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	fill_pickups_from_map(t_app *app, t_pickup *items)
{
	int		x;
	int		y;
	int		i;
	char	c;

	i = 0;
	y = 0;
	while (y < app->map.height)
	{
		x = 0;
		while (app->map.grid[y][x])
		{
			c = app->map.grid[y][x];
			if (bonus_is_sprite_tile(c))
			{
				items[i].x = x + 0.5;
				items[i].y = y + 0.5;
				items[i].type = c;
				items[i].collected = 0;
				i++;
			}
			x++;
		}
		y++;
	}
}

int	bonus_pickups_rebuild(t_app *app)
{
	t_bonus_pickups	*pickups;
	t_pickup		*items;
	int				count;

	if (!app || !app->map.grid)
		return (1);
	pickups = &app->bonus.pickups;
	count = count_map_pickups(app);
	items = NULL;
	if (count > 0)
	{
		items = malloc(sizeof(*items) * (size_t)count);
		if (!items)
			return (1);
		fill_pickups_from_map(app, items);
	}
	free(pickups->items);
	pickups->items = items;
	pickups->count = count;
	pickups->cap = count;
	return (0);
}

void	bonus_pickups_shutdown(t_app *app)
{
	if (!app)
		return ;
	free(app->bonus.pickups.items);
	app->bonus.pickups.items = NULL;
	app->bonus.pickups.count = 0;
	app->bonus.pickups.cap = 0;
}
