/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_api.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 14:40:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_door_tile(char c)
{
	return (ft_strchr(BONUS_DOOR_SET, c) != NULL);
}

static int	scan_doors(t_app *app, int fill)
{
	int		x;
	int		y;
	int		count;

	y = 0;
	count = 0;
	while (y < app->map.height)
	{
		x = 0;
		while (app->map.grid[y][x])
		{
			if (is_door_tile(app->map.grid[y][x]))
			{
				if (fill)
					app->bonus.doors.items[count] = (t_door){x, y,
						DOOR_CLOSED, 0.0, 0.0};
				count++;
			}
			x++;
		}
		y++;
	}
	return (count);
}

int	bonus_doors_init(t_app *app)
{
	int	count;

	if (!app)
		return (1);
	app->bonus.doors.items = NULL;
	app->bonus.doors.count = 0;
	app->bonus.doors.cap = 0;
	app->bonus.doors.interact_cooldown = BONUS_DOOR_INTERACT_COOLDOWN;
	app->bonus.doors.interact_timer = 0.0;
	count = scan_doors(app, 0);
	if (count <= 0)
		return (0);
	app->bonus.doors.items = malloc(sizeof(t_door) * count);
	if (!app->bonus.doors.items)
		return (1);
	app->bonus.doors.count = count;
	app->bonus.doors.cap = count;
	scan_doors(app, 1);
	return (0);
}

void	bonus_doors_update(t_app *app)
{
	t_door	*door;
	int		i;

	if (!app || app->bonus.retro.enabled == 0)
		return ;
	i = 0;
	while (i < app->bonus.doors.count)
	{
		door = &app->bonus.doors.items[i++];
		door->state_timer += app->delta_time;
		if (door->state == DOOR_OPENING)
			door->open_progress += app->delta_time * BONUS_DOOR_SPEED;
		else if (door->state == DOOR_CLOSING)
			door->open_progress -= app->delta_time * BONUS_DOOR_SPEED;
		if (door->open_progress >= 1.0)
			*door = (t_door){door->x, door->y, DOOR_OPEN, 1.0, 0.0};
		else if (door->open_progress <= 0.0)
			*door = (t_door){door->x, door->y, DOOR_CLOSED, 0.0, 0.0};
	}
	if (app->bonus.doors.interact_timer <= 0.0)
		return ;
	app->bonus.doors.interact_timer -= app->delta_time;
	if (app->bonus.doors.interact_timer < 0.0)
		app->bonus.doors.interact_timer = 0.0;
}

void	bonus_doors_shutdown(t_app *app)
{
	if (!app)
		return ;
	free(app->bonus.doors.items);
	app->bonus.doors.items = NULL;
	app->bonus.doors.count = 0;
	app->bonus.doors.cap = 0;
	app->bonus.doors.interact_cooldown = BONUS_DOOR_INTERACT_COOLDOWN;
	app->bonus.doors.interact_timer = 0.0;
}
