/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:32:29 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/08 09:41:27 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_app *app, double x, double y)
{
	int	map_x;
	int	map_y;
	int	height;
	int	row_len;

	map_x = (int)x;
	map_y = (int)y;
	height = app->line_count - app->map_start;
	if (map_y < 0 || map_y >= height)
		return (1);
	row_len = ft_strlen(app->file_lines[app->map_start + map_y]);
	if (map_x < 0 || map_x >= row_len)
		return (1);
	if (app->file_lines[app->map_start + map_y][map_x] == '1')
		return (1);
	return (0);
}

static void	try_move(t_app *app, double dx, double dy)
{
	double	next_x;
	double	next_y;

	next_x = app->player_x + dx;
	next_y = app->player_y + dy;
	if (is_wall(app, next_x, next_y) == 0)
	{
		app->player_x = next_x;
		app->player_y = next_y;
	}
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
