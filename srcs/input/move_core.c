/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 05:20:00 by brrr1            #+#    #+#             */
/*   Updated: 2026/04/05 05:20:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_walkable(t_app *app, double x, double y)
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
	return (cell == '0' || cell == 'N' || cell == 'S'
		|| cell == 'E' || cell == 'W');
}

static int	is_position_clear(t_app *app, double x, double y)
{
	const double	r = COLLISION_RADIUS;

	return (is_walkable(app, x, y)
		&& is_walkable(app, x + r, y)
		&& is_walkable(app, x - r, y)
		&& is_walkable(app, x, y + r)
		&& is_walkable(app, x, y - r)
		&& is_walkable(app, x + r, y + r)
		&& is_walkable(app, x + r, y - r)
		&& is_walkable(app, x - r, y + r)
		&& is_walkable(app, x - r, y - r));
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
		if (is_position_clear(app, next, app->player.y))
			app->player.x = next;
		next = app->player.y + step_y;
		if (is_position_clear(app, app->player.x, next))
			app->player.y = next;
		i++;
	}
}
