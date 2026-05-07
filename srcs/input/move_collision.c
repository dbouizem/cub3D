/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeceiro <bbeceiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 05:20:00 by bbeceiro            #+#    #+#             */
/*   Updated: 2026/04/05 05:20:00 by bbeceiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_door_tile(char c)
{
	return (ft_strchr(BONUS_DOOR_SET, c) != NULL);
}

/*
** Bonus hooks:
** mandatory treats sprite and door checks as false through no-op functions.
*/
static int	is_walkable(t_app *app, double x, double y, int axis)
{
	int		map_x;
	int		map_y;
	int		row_len;
	char	cell;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= app->map.height)
		return (0);
	row_len = (int)ft_strlen(app->map.grid[map_y]);
	if (map_x < 0 || map_x >= row_len)
		return (0);
	cell = app->map.grid[map_y][map_x];
	if (cell == '0' || cell == 'N' || cell == 'S'
		|| cell == 'E' || cell == 'W')
		return (1);
	if (bonus_is_sprite_tile(cell))
		return (1);
	if (is_door_tile(cell) && bonus_door_blocks_axis(app, x, y, axis) == 0)
		return (1);
	return (0);
}

static int	is_position_clear(t_app *app, double x, double y, int axis)
{
	const double	r = COLLISION_RADIUS;

	return (is_walkable(app, x, y, axis)
		&& is_walkable(app, x + r, y, axis)
		&& is_walkable(app, x - r, y, axis)
		&& is_walkable(app, x, y + r, axis)
		&& is_walkable(app, x, y - r, axis)
		&& is_walkable(app, x + r, y + r, axis)
		&& is_walkable(app, x + r, y - r, axis)
		&& is_walkable(app, x - r, y + r, axis)
		&& is_walkable(app, x - r, y - r, axis));
}

static int	compute_steps(double dx, double dy)
{
	double	max_abs;
	double	max_step;
	int		steps;

	max_abs = fabs(dx);
	if (fabs(dy) > max_abs)
		max_abs = fabs(dy);
	max_step = COLLISION_RADIUS * 0.30;
	steps = (int)(max_abs / max_step) + 1;
	if (steps < 1)
		return (1);
	return (steps);
}

void	move_with_collision(t_app *app, double dx, double dy)
{
	double	step_x;
	double	step_y;
	double	next;
	int		steps;
	int		i;

	steps = compute_steps(dx, dy);
	step_x = dx / (double)steps;
	step_y = dy / (double)steps;
	i = 0;
	while (i < steps)
	{
		next = app->player.x + step_x;
		if (is_position_clear(app, next, app->player.y, 0))
			app->player.x = next;
		next = app->player.y + step_y;
		if (is_position_clear(app, app->player.x, next, 1))
			app->player.y = next;
		i++;
	}
}
