/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bonus_hud_reset_state(t_app *app)
{
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

static void	update_face_state(t_app *app, t_bonus_hud *hud)
{
	hud->face_idle_timer += app->delta_time;
	if (hud->face_idle_timer >= BONUS_HUD_FACE_IDLE_TIME)
	{
		hud->face_idle_timer = 0.0;
		hud->face_idle_frame = (hud->face_idle_frame + 1) % 3;
	}
	if (hud->face_react_timer > 0.0)
	{
		hud->face_react_timer -= app->delta_time;
		if (hud->face_react_timer <= 0.0)
		{
			hud->face_react_timer = 0.0;
			hud->face_react = 0;
		}
	}
}

static void	update_turn_state(t_app *app, t_bonus_hud *hud)
{
	if (app->input.turn_left)
		hud->face_turn_dir = -1;
	else if (app->input.turn_right)
		hud->face_turn_dir = 1;
	else
	{
		hud->face_turn_dir = 0;
		hud->face_prev_angle = atan2(app->dir_y, app->dir_x);
	}
}

static void	update_weapon_state(t_app *app, t_bonus_hud *hud)
{
	if (hud->weapon_cooldown > 0.0)
	{
		hud->weapon_cooldown -= app->delta_time;
		if (hud->weapon_cooldown < 0.0)
			hud->weapon_cooldown = 0.0;
	}
	if (hud->weapon_frame <= 0)
		return ;
	hud->weapon_timer += app->delta_time;
	while (hud->weapon_timer >= BONUS_WEAPON_FRAME_TIME
		&& hud->weapon_frame > 0)
	{
		hud->weapon_timer -= BONUS_WEAPON_FRAME_TIME;
		hud->weapon_frame++;
		if (hud->weapon_frame > BONUS_WEAPON_SHOOT_FRAMES)
			hud->weapon_frame = 0;
	}
}

void	bonus_hud_update(t_app *app)
{
	t_bonus_hud	*hud;

	if (!app)
		return ;
	hud = &app->bonus.hud;
	update_face_state(app, hud);
	update_turn_state(app, hud);
	update_weapon_state(app, hud);
}
