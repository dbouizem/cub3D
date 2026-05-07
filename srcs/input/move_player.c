/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeceiro <bbeceiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 05:20:00 by bbeceiro            #+#    #+#             */
/*   Updated: 2026/04/05 05:20:00 by bbeceiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_app *app)
{
	move_with_collision(app, app->dir_x * MOVE_SPEED * app->delta_time,
		app->dir_y * MOVE_SPEED * app->delta_time);
}

void	move_backward(t_app *app)
{
	move_with_collision(app,
		-app->dir_x * MOVE_SPEED * app->delta_time,
		-app->dir_y * MOVE_SPEED * app->delta_time);
}

void	strafe_left(t_app *app)
{
	move_with_collision(app, app->dir_y * MOVE_SPEED * app->delta_time,
		-app->dir_x * MOVE_SPEED * app->delta_time);
}

void	strafe_right(t_app *app)
{
	move_with_collision(app, -app->dir_y * MOVE_SPEED * app->delta_time,
		app->dir_x * MOVE_SPEED * app->delta_time);
}
