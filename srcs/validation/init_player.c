/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeceiro <bbeceiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:33:43 by bbeceiro          #+#    #+#             */
/*   Updated: 2026/05/07 14:33:46 by bbeceiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_north(t_app *app)
{
	app->dir_x = 0.0;
	app->dir_y = -1.0;
	app->plane_x = 0.66;
	app->plane_y = 0.0;
}

static void	set_south(t_app *app)
{
	app->dir_x = 0.0;
	app->dir_y = 1.0;
	app->plane_x = -0.66;
	app->plane_y = 0.0;
}

static void	set_east(t_app *app)
{
	app->dir_x = 1.0;
	app->dir_y = 0.0;
	app->plane_x = 0.0;
	app->plane_y = 0.66;
}

static void	set_west(t_app *app)
{
	app->dir_x = -1.0;
	app->dir_y = 0.0;
	app->plane_x = 0.0;
	app->plane_y = -0.66;
}

void	init_player_directions(t_app *app)
{
	if (app->player_dir == 'N')
		set_north(app);
	else if (app->player_dir == 'S')
		set_south(app);
	else if (app->player_dir == 'E')
		set_east(app);
	else if (app->player_dir == 'W')
		set_west(app);
}
