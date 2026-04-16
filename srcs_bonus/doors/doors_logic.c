/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bonus_door_allows_passage_at(t_app *app, int x, int y, double hit)
{
	char	tile;
	double	progress;

	tile = bonus_map_cell_at(app, x, y);
	if (!bonus_is_door_tile(tile))
		return (0);
	progress = bonus_door_open_progress_at(app, x, y);
	if (progress <= 0.0)
		return (0);
	if (progress >= 1.0)
		return (1);
	if (tile == 'A')
		return (progress >= BONUS_DOOR_PASSABLE);
	return (hit > 0.5 - progress * 0.5 && hit < 0.5 + progress * 0.5);
}

int	bonus_door_blocks_axis(t_app *app, double px, double py, int axis)
{
	double	hit;

	if (!bonus_is_door_tile(bonus_map_cell_at(app, (int)px, (int)py)))
		return (0);
	if (axis == 0)
		hit = py - floor(py);
	else
		hit = px - floor(px);
	return (!bonus_door_allows_passage_at(app, (int)px, (int)py, hit));
}

int	bonus_door_is_occupied(t_app *app, t_door *door)
{
	double	nearest_x;
	double	nearest_y;
	double	dx;
	double	dy;

	if (!app || !door)
		return (0);
	nearest_x = fmin(fmax(app->player.x, door->x), door->x + 1.0);
	nearest_y = fmin(fmax(app->player.y, door->y), door->y + 1.0);
	dx = app->player.x - nearest_x;
	dy = app->player.y - nearest_y;
	return (dx * dx + dy * dy < COLLISION_RADIUS * COLLISION_RADIUS);
}
