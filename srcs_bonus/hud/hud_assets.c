/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_assets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 19:25:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/10 19:25:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_face_lists(t_app *app, t_bonus_hud *hud)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 5)
	{
		j = -1;
		while (++j < 3)
			if (bonus_sprite_load_tex(app, &hud->face_straight[i][j],
				bonus_face_straight_path(i, j)))
				return (1);
		if (bonus_sprite_load_tex(app, &hud->face_left[i],
				bonus_face_left_path(i))
			|| bonus_sprite_load_tex(app, &hud->face_right[i],
				bonus_face_right_path(i))
			|| bonus_sprite_load_tex(app, &hud->face_ouch[i],
				bonus_face_ouch_path(i))
			|| bonus_sprite_load_tex(app, &hud->face_kill[i],
				bonus_face_kill_path(i)))
			return (1);
	}
	return (bonus_sprite_load_tex(app, &hud->face_dead,
			"textures/bonus/player/stfdead0.xpm"));
}

static void	destroy_face_lists(t_app *app, t_bonus_hud *hud)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 5)
	{
		j = -1;
		while (++j < 3)
			bonus_sprite_destroy_tex(app, &hud->face_straight[i][j]);
		bonus_sprite_destroy_tex(app, &hud->face_left[i]);
		bonus_sprite_destroy_tex(app, &hud->face_right[i]);
		bonus_sprite_destroy_tex(app, &hud->face_ouch[i]);
		bonus_sprite_destroy_tex(app, &hud->face_kill[i]);
	}
	bonus_sprite_destroy_tex(app, &hud->face_dead);
}

int	bonus_hud_init(t_app *app)
{
	t_bonus_hud	*hud;

	if (!app || !app->mlx_ptr)
		return (1);
	hud = &app->bonus.hud;
	bonus_hud_reset_state(app);
	hud->face_prev_angle = atan2(app->dir_y, app->dir_x);
	if (load_face_lists(app, hud))
		return (1);
	if (bonus_sprite_load_tex(app, &hud->weapon_idle, BONUS_WEAPON_IDLE_1_XPM))
		return (bonus_hud_shutdown(app), 1);
	if (bonus_sprite_load_tex(app, &hud->weapon_shoot[0],
			BONUS_WEAPON_SHOOT_1_XPM))
		return (bonus_hud_shutdown(app), 1);
	if (bonus_sprite_load_tex(app, &hud->weapon_shoot[1],
			BONUS_WEAPON_SHOOT_2_XPM))
		return (bonus_hud_shutdown(app), 1);
	if (bonus_sprite_load_tex(app, &hud->weapon_shoot[2],
			BONUS_WEAPON_SHOOT_3_XPM))
		return (bonus_hud_shutdown(app), 1);
	return (0);
}

void	bonus_hud_shutdown(t_app *app)
{
	t_bonus_hud	*hud;

	if (!app)
		return ;
	hud = &app->bonus.hud;
	destroy_face_lists(app, hud);
	bonus_sprite_destroy_tex(app, &hud->weapon_idle);
	bonus_sprite_destroy_tex(app, &hud->weapon_shoot[0]);
	bonus_sprite_destroy_tex(app, &hud->weapon_shoot[1]);
	bonus_sprite_destroy_tex(app, &hud->weapon_shoot[2]);
	bonus_hud_reset_state(app);
}
