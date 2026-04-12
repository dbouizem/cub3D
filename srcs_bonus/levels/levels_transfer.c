/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_transfer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:15:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 19:15:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	null_next_level(t_app *next)
{
	next->config.tex_no = NULL;
	next->config.tex_so = NULL;
	next->config.tex_we = NULL;
	next->config.tex_ea = NULL;
	next->map.grid = NULL;
	next->map.height = 0;
	next->bonus.doors.items = NULL;
	next->bonus.doors.count = 0;
	next->bonus.doors.cap = 0;
	next->bonus.pickups.items = NULL;
	next->bonus.pickups.count = 0;
	next->bonus.pickups.cap = 0;
}

void	bonus_transfer_next_level(t_app *app, t_app *next, t_img tex[4])
{
	app->config = next->config;
	app->map = next->map;
	app->player = next->player;
	app->bonus.doors = next->bonus.doors;
	app->bonus.pickups = next->bonus.pickups;
	app->tex_no = tex[0];
	app->tex_so = tex[1];
	app->tex_we = tex[2];
	app->tex_ea = tex[3];
	null_next_level(next);
}
