/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:30:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 18:30:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_vectors(t_app *app)
{
	if (app->player.orientation == 'N' || app->player.orientation == 'S')
	{
		app->dir_x = 0;
		app->plane_y = 0;
		app->dir_y = -1;
		app->plane_x = FOV_FACTOR;
		if (app->player.orientation == 'S')
			app->dir_y = 1;
		if (app->player.orientation == 'S')
			app->plane_x = -FOV_FACTOR;
	}
	else
	{
		app->dir_y = 0;
		app->plane_x = 0;
		app->dir_x = -1;
		app->plane_y = -FOV_FACTOR;
		if (app->player.orientation == 'E')
			app->dir_x = 1;
		if (app->player.orientation == 'E')
			app->plane_y = FOV_FACTOR;
	}
}
