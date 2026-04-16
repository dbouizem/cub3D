/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_query.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:41:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 14:41:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bonus_door_try_toggle(t_app *app)
{
	t_door	*door;
	int		tx;
	int		ty;

	if (!app || app->bonus.retro.enabled == 0)
		return (0);
	if (app->bonus.doors.interact_timer > 0.0)
		return (0);
	if (!bonus_find_front_door(app, &tx, &ty))
		return (0);
	door = bonus_find_door(app, tx, ty);
	if (!door)
		return (0);
	bonus_toggle_door_state(app, door);
	app->bonus.doors.interact_timer = app->bonus.doors.interact_cooldown;
	return (1);
}

int	bonus_door_is_open_at(t_app *app, int x, int y)
{
	t_door	*door;

	if (!app)
		return (0);
	door = bonus_find_door(app, x, y);
	if (!door)
		return (0);
	return (door->open_progress >= BONUS_DOOR_PASSABLE);
}

int	bonus_door_is_blocking(t_app *app, double px, double py)
{
	if (bonus_door_blocks_axis(app, px, py, 0))
		return (1);
	return (bonus_door_blocks_axis(app, px, py, 1));
}

double	bonus_door_open_progress_at(t_app *app, int x, int y)
{
	t_door	*door;

	if (!app)
		return (0.0);
	door = bonus_find_door(app, x, y);
	if (!door)
		return (0.0);
	return (door->open_progress);
}

int	bonus_door_state_at(t_app *app, int x, int y)
{
	t_door	*door;

	if (!app)
		return (DOOR_CLOSED);
	door = bonus_find_door(app, x, y);
	if (!door)
		return (DOOR_CLOSED);
	return (door->state);
}
