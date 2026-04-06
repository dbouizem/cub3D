/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:32:29 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/06 16:45:59 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	handle_movement(t_app *app)
{
	if (app->keys.w == TRUE)
	{
		app->player_x += app->dir_x * MOVE_SPEED;
		app->player_y += app->dir_y * MOVE_SPEED;
	}
	if (app->keys.s == TRUE)
	{
		app->player_x -= app->dir_x * MOVE_SPEED;
		app->player_y -= app->dir_y * MOVE_SPEED;
	}
	if (app->keys.d == TRUE)
	{
		app->player_x += -app->dir_y * MOVE_SPEED;
		app->player_y += app->dir_x * MOVE_SPEED;
	}
	if (app->keys.a == TRUE)
	{
		app->player_x -= -app->dir_y * MOVE_SPEED;
		app->player_y -= app->dir_x * MOVE_SPEED;
	}
}
