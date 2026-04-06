/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:23:16 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/06 10:33:32 by brrr1            ###   ########.fr       */
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
