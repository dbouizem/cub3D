/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:52:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/10 15:52:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img	*bonus_pick_sprite_texture(t_app *app, char type)
{
	if (!app)
		return (NULL);
	if (type == '*')
		return (&app->bonus.sprites.pickup_hp);
	if (type == '@')
		return (&app->bonus.sprites.pickup_ammo);
	if (type == ')')
		return (&app->bonus.sprites.pickup_armor);
	if (type == '/')
		return (&app->bonus.sprites.pickup_frames
			[app->bonus.sprites.anim_frame]);
	return (NULL);
}

void	bonus_shift_sprite_space(t_bonus_sprites *sp, t_player *pl, double sign)
{
	int	i;

	i = -1;
	while (++i < sp->count)
	{
		sp->xs[i] += pl->x * sign;
		sp->ys[i] += pl->y * sign;
	}
}
