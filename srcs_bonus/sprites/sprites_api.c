/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_api.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 10:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/10 10:55:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bonus_is_sprite_tile(char c)
{
	return (ft_strchr(BONUS_SPRITE_SET, c) != NULL);
}

int	bonus_sprites_rebuild(t_app *app)
{
	if (!app || !app->map.grid)
		return (1);
	if (bonus_sprite_ensure_cap(&app->bonus.sprites,
			bonus_pickups_count_active(app)) != 0)
		return (1);
	bonus_pickups_fill_active_sprites(app);
	return (0);
}

static int	load_pickup_textures(t_app *app, t_bonus_sprites *sp)
{
	if (bonus_sprite_load_tex(app, &sp->pickup_frames[0],
			BONUS_PICKUP_FRAME_1_XPM) != 0)
		return (1);
	if (bonus_sprite_load_tex(app, &sp->pickup_frames[1],
			BONUS_PICKUP_FRAME_2_XPM) != 0)
		return (1);
	if (bonus_sprite_load_tex(app, &sp->pickup_frames[2],
			BONUS_PICKUP_FRAME_3_XPM) != 0)
		return (1);
	if (bonus_sprite_load_tex(app, &sp->pickup_frames[3],
			BONUS_PICKUP_FRAME_4_XPM) != 0)
		return (1);
	if (bonus_sprite_load_tex(app, &sp->pickup_hp, BONUS_PICKUP_HP_XPM) != 0)
		return (1);
	if (bonus_sprite_load_tex(app, &sp->pickup_ammo,
			BONUS_PICKUP_AMMO_XPM) != 0)
		return (1);
	return (bonus_sprite_load_tex(app, &sp->pickup_armor,
			BONUS_PICKUP_ARMOR_XPM));
}

static int	init_sprite_storage(t_app *app, t_bonus_sprites *sp)
{
	ft_bzero(sp, sizeof(*sp));
	sp->zbuf = malloc(sizeof(double) * (size_t)app->win_w);
	if (!sp->zbuf)
		return (1);
	sp->zcap = app->win_w;
	sp->anim_frame = 0;
	sp->anim_timer = 0.0;
	if (bonus_pickups_rebuild(app) != 0)
		return (1);
	return (0);
}

int	bonus_sprites_init(t_app *app)
{
	t_bonus_sprites	*sp;

	if (!app || !app->mlx_ptr || app->win_w <= 0)
		return (1);
	sp = &app->bonus.sprites;
	if (init_sprite_storage(app, sp) != 0)
		return (bonus_sprites_shutdown(app), 1);
	if (load_pickup_textures(app, sp) != 0)
		return (bonus_sprites_shutdown(app), 1);
	if (bonus_sprites_rebuild(app) != 0)
		return (bonus_sprites_shutdown(app), 1);
	return (0);
}
