/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 08:55:58 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/09 09:58:26 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_vectors_left(t_app *app)
{
	double	old_dir_x;
	double	old_plane_x;
	double	old_plane_y;
	double	cos_rot;
	double	sin_rot;

	cos_rot = cos(-ROT_SPEED);
	sin_rot = sin(-ROT_SPEED);
	old_dir_x = app->dir_x;
	app->dir_x = app->dir_x * cos_rot - app->dir_y * sin_rot;
	app->dir_y = old_dir_x * sin_rot + app->dir_y * cos_rot;
	old_plane_x = app->plane_x;
	old_plane_y = app->plane_y;
	app->plane_x = app->plane_x * cos_rot - app->plane_y * sin_rot;
	app->plane_y = old_plane_x * sin_rot + old_plane_y * cos_rot;
}

static void	rotate_vectors_right(t_app *app)
{
	double	old_dir_x;
	double	old_plane_x;
	double	old_plane_y;
	double	cos_rot;
	double	sin_rot;

	cos_rot = cos(ROT_SPEED);
	sin_rot = sin(ROT_SPEED);
	old_dir_x = app->dir_x;
	app->dir_x = app->dir_x * cos_rot - app->dir_y * sin_rot;
	app->dir_y = old_dir_x * sin_rot + app->dir_y * cos_rot;
	old_plane_x = app->plane_x;
	old_plane_y = app->plane_y;
	app->plane_x = app->plane_x * cos_rot - app->plane_y * sin_rot;
	app->plane_y = old_plane_x * sin_rot + old_plane_y * cos_rot;
}

void	handle_rotation(t_app *app)
{
	if (app->keys.left)
		rotate_vectors_left(app);
	if (app->keys.right)
		rotate_vectors_right(app);
}
