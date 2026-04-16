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
	app->frame_count = 0;
	app->dir_x = 0.0;
	app->dir_y = 0.0;
	app->plane_x = 0.0;
	app->plane_y = 0.0;
}

static void	init_bonus_state(t_app *app)
{
	app->bonus.retro.enabled = 0;
	app->bonus.retro.minimap_zoom = BONUS_MINIMAP_ZOOM_DEFAULT;
	app->bonus.stats.hp = BONUS_HP_START;
	app->bonus.stats.armor = BONUS_ARMOR_START;
	app->bonus.stats.ammo = BONUS_AMMO_START;
	app->bonus.stats.score = BONUS_SCORE_START;
	app->bonus.sprites.anim_frame = 0;
	app->bonus.sprites.anim_timer = 0.0;
	app->bonus.hud.weapon_frame = 0;
	app->bonus.hud.weapon_timer = 0.0;
	app->bonus.hud.weapon_cooldown = 0.0;
	app->bonus.hud.face_react = 0;
	app->bonus.hud.face_react_timer = 0.0;
	app->bonus.hud.face_idle_timer = 0.0;
	app->bonus.hud.face_idle_frame = 0;
	app->bonus.hud.face_turn_dir = 0;
	app->bonus.hud.face_prev_angle = 0.0;
}

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

void	init_app(t_app *app)
{
	ft_bzero(app, sizeof(*app));
	init_defaults(app);
	init_tex(&app->frame);
	init_tex(&app->tex_no);
	init_tex(&app->tex_so);
	init_tex(&app->tex_we);
	init_tex(&app->tex_ea);
	init_tex(&app->bonus.retro.fb);
	init_tex(&app->bonus.retro.out);
	init_tex(&app->bonus.retro.minimap);
	init_tex(&app->bonus.sprites.pickup_frames[0]);
	init_tex(&app->bonus.sprites.pickup_frames[1]);
	init_tex(&app->bonus.sprites.pickup_frames[2]);
	init_tex(&app->bonus.sprites.pickup_frames[3]);
	init_tex(&app->bonus.hud.face_dead);
	init_tex(&app->bonus.hud.weapon_idle);
	init_tex(&app->bonus.hud.weapon_shoot[0]);
	init_tex(&app->bonus.hud.weapon_shoot[1]);
	init_tex(&app->bonus.hud.weapon_shoot[2]);
	init_bonus_state(app);
}
