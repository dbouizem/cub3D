/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:32:29 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/12 07:14:01 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_app *app, double x, double y)
{
	int		map_x;
	int		map_y;
	int		height;
	int		row_len;
	char	cell;

	if (x < 0.0 || y < 0.0)
		return (1);
	map_x = (int)x;
	map_y = (int)y;
	height = app->line_count - app->map_start;
	if (map_y < 0 || map_y >= height)
		return (1);
	row_len = ft_strlen(app->file_lines[app->map_start + map_y]);
	if (map_x < 0 || map_x >= row_len)
		return (1);
	cell = app->file_lines[app->map_start + map_y][map_x];
	if (cell == '1' || cell == ' ')
		return (1);
	return (0);
}

static int	can_move_to(t_app *app, double x, double y)
{
	if (is_wall(app, x - PLAYER_RADIUS, y - PLAYER_RADIUS) != 0)
		return (0);
	if (is_wall(app, x + PLAYER_RADIUS, y - PLAYER_RADIUS) != 0)
		return (0);
	if (is_wall(app, x - PLAYER_RADIUS, y + PLAYER_RADIUS) != 0)
		return (0);
	if (is_wall(app, x + PLAYER_RADIUS, y + PLAYER_RADIUS) != 0)
		return (0);
	return (1);
}

static void	try_move(t_app *app, double dx, double dy)
{
	double	next_x;
	double	next_y;

	next_x = app->player_x + dx;
	next_y = app->player_y + dy;
	if (can_move_to(app, next_x, app->player_y) != 0)
		app->player_x = next_x;
	if (can_move_to(app, app->player_x, next_y) != 0)
		app->player_y = next_y;
}

void	handle_movement(t_app *app)
{
	if (app->keys.w == TRUE)
		try_move(app, app->dir_x * MOVE_SPEED, app->dir_y * MOVE_SPEED);
	if (app->keys.s == TRUE)
		try_move(app, -app->dir_x * MOVE_SPEED, -app->dir_y * MOVE_SPEED);
	if (app->keys.d == TRUE)
		try_move(app, -app->dir_y * MOVE_SPEED, app->dir_x * MOVE_SPEED);
	if (app->keys.a == TRUE)
		try_move(app, app->dir_y * MOVE_SPEED, -app->dir_x * MOVE_SPEED);
}
