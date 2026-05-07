/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <dbouizem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 05:20:00 by bbeceiro          #+#    #+#             */
/*   Updated: 2026/05/07 18:38:05 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	apply_move_keys(t_app *app)
{
	if (app->input.forward)
		move_forward(app);
	if (app->input.backward)
		move_backward(app);
	if (app->input.left)
		strafe_left(app);
	if (app->input.right)
		strafe_right(app);
}

static void	apply_turn_keys(t_app *app)
{
	if (app->input.turn_left)
		rotate_left(app);
	if (app->input.turn_right)
		rotate_right(app);
}

void	update_player_input(t_app *app)
{
	apply_move_keys(app);
	apply_turn_keys(app);
	apply_mouse_look(app);
}
