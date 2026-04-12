/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_shutdown.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 18:55:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_pickup_textures(t_app *app, t_bonus_sprites *sp)
{
	bonus_sprite_destroy_tex(app, &sp->pickup_frames[0]);
	bonus_sprite_destroy_tex(app, &sp->pickup_frames[1]);
	bonus_sprite_destroy_tex(app, &sp->pickup_frames[2]);
	bonus_sprite_destroy_tex(app, &sp->pickup_frames[3]);
	bonus_sprite_destroy_tex(app, &sp->pickup_hp);
	bonus_sprite_destroy_tex(app, &sp->pickup_ammo);
	bonus_sprite_destroy_tex(app, &sp->pickup_armor);
}

void	bonus_sprites_shutdown(t_app *app)
{
	t_bonus_sprites	*sp;

	if (!app)
		return ;
	sp = &app->bonus.sprites;
	destroy_pickup_textures(app, sp);
	free(sp->zbuf);
	free(sp->xs);
	free(sp->ys);
	free(sp->types);
	free(sp->active);
	free(sp->dists);
	ft_bzero(sp, sizeof(*sp));
}
