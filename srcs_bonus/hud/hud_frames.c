/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_frames.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*bonus_weapon_current_frame(t_app *app)
{
	t_bonus_hud	*hud;

	hud = &app->bonus.hud;
	if (!hud->weapon_idle.addr)
		return (NULL);
	if (hud->weapon_frame <= 0 || app->bonus.stats.ammo < 0)
		return (&hud->weapon_idle);
	return (&hud->weapon_shoot[hud->weapon_frame - 1]);
}

static int	face_health_band(t_app *app)
{
	if (app->bonus.stats.hp <= 0)
		return (4);
	if (app->bonus.stats.hp < 20)
		return (4);
	if (app->bonus.stats.hp < 40)
		return (3);
	if (app->bonus.stats.hp < 60)
		return (2);
	if (app->bonus.stats.hp < 80)
		return (1);
	return (0);
}

t_img	*bonus_face_current_frame(t_app *app)
{
	t_bonus_hud	*hud;
	int			band;

	hud = &app->bonus.hud;
	if (app->bonus.stats.hp <= 0)
		return (&hud->face_dead);
	band = face_health_band(app);
	if (hud->face_react)
		return (&hud->face_ouch[band]);
	if (band >= 4)
		return (&hud->face_kill[band]);
	if (hud->face_turn_dir < 0)
		return (&hud->face_left[band]);
	if (hud->face_turn_dir > 0)
		return (&hud->face_right[band]);
	return (&hud->face_straight[band][hud->face_idle_frame]);
}
