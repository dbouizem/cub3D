/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeceiro <bbeceiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:28:43 by bbeceiro          #+#    #+#             */
/*   Updated: 2026/05/07 14:28:46 by bbeceiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_app(t_app *app)
{
	ft_bzero(app, sizeof(*app));
	app->config.floor_rgb[0] = -1;
	app->config.floor_rgb[1] = -1;
	app->config.floor_rgb[2] = -1;
	app->config.ceiling_rgb[0] = -1;
	app->config.ceiling_rgb[1] = -1;
	app->config.ceiling_rgb[2] = -1;
	app->win_w = WIN_W;
	app->win_h = WIN_H;
	app->player_x = 0.0;
	app->player_y = 0.0;
	app->dir_x = 0.0;
	app->dir_y = 0.0;
	app->plane_x = 0.0;
	app->plane_y = 0.0;
	app->player_dir = ' ';
}
