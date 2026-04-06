/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:23:16 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/05 05:20:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_tex(t_img *tex)
{
	tex->img_ptr = NULL;
	tex->addr = NULL;
	tex->width = 0;
	tex->height = 0;
	tex->bpp = 0;
	tex->line_len = 0;
	tex->endian = 0;
}

static void	init_defaults(t_app *app)
{
	app->config.floor_rgb[0] = -1;
	app->config.floor_rgb[1] = -1;
	app->config.floor_rgb[2] = -1;
	app->config.ceiling_rgb[0] = -1;
	app->config.ceiling_rgb[1] = -1;
	app->config.ceiling_rgb[2] = -1;
	app->map.grid = NULL;
	app->map.height = 0;
	app->player.x = 0.0;
	app->player.y = 0.0;
	app->player.orientation = '\0';
	app->win_w = WIN_W;
	app->win_h = WIN_H;
	app->delta_time = FRAME_DT_DEFAULT;
	app->last_frame_time = 0.0;
	app->dir_x = 0.0;
	app->dir_y = 0.0;
	app->plane_x = 0.0;
	app->plane_y = 0.0;
}

void	init_app(t_app *app)
{
	ft_bzero(app, sizeof(*app));
	init_defaults(app);
	init_tex(&app->frame);
	init_tex(&app->tex_no);
	init_tex(&app->tex_so);
	init_tex(&app->tex_we);
	init_tex(&app->tex_ea);
	init_tex(&app->bonus_fb);
	init_tex(&app->bonus_out);
	app->bonus_on = 0;
}

static void	set_direction_ns(t_app *app)
{
	if (app->player.orientation == 'N')
	{
		app->dir_x = 0;
		app->dir_y = -1;
		app->plane_x = FOV_FACTOR;
		app->plane_y = 0;
	}
	else if (app->player.orientation == 'S')
	{
		app->dir_x = 0;
		app->dir_y = 1;
		app->plane_x = -FOV_FACTOR;
		app->plane_y = 0;
	}
}

void	init_player_vectors(t_app *app)
{
	if (app->player.orientation == 'N' || app->player.orientation == 'S')
		return (set_direction_ns(app));
	else if (app->player.orientation == 'E')
	{
		app->dir_x = 1;
		app->dir_y = 0;
		app->plane_x = 0;
		app->plane_y = FOV_FACTOR;
	}
	else
	{
		app->dir_x = -1;
		app->dir_y = 0;
		app->plane_x = 0;
		app->plane_y = -FOV_FACTOR;
	}
}
