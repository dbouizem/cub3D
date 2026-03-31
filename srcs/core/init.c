/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:23:16 by dbouizem          #+#    #+#             */
/*   Updated: 2026/03/31 17:23:16 by dbouizem         ###   ########.fr       */
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
}
