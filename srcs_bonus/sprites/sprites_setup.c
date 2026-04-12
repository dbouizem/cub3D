/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_setup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	setup_sprite_camera(t_app *app, int i, t_sprite_proj *p)
{
	double	inv;
	double	tx;

	inv = 1.0 / (app->plane_x * app->dir_y - app->dir_x * app->plane_y);
	tx = inv * (app->dir_y * app->bonus.sprites.xs[i] - app->dir_x
			* app->bonus.sprites.ys[i]);
	p->sy = inv * (-app->plane_y * app->bonus.sprites.xs[i] + app->plane_x
			* app->bonus.sprites.ys[i]);
	if (p->sy <= 0.0)
		return (1);
	p->sx = (int)((app->frame.width / 2) * (1.0 + tx / p->sy));
	return (0);
}

static double	sprite_scale(char type)
{
	double	scale;

	scale = BONUS_SPRITE_SCALE;
	if (type == '@')
		scale *= BONUS_PICKUP_AMMO_SCALE;
	else if (type == ')')
		scale *= BONUS_PICKUP_ARMOR_SCALE;
	else if (type == '/')
		scale *= BONUS_PICKUP_SCORE_SCALE;
	return (scale);
}

static void	setup_sprite_size(t_app *app, int i, t_sprite_proj *p, t_img *tex)
{
	p->sh = (int)((app->frame.height / (p->sy + 1e-9))
			* sprite_scale(app->bonus.sprites.types[i]));
	if (p->sh < 1)
		p->sh = 1;
	p->sw = p->sh;
	if (tex && tex->addr && p->ty1 >= p->ty0)
		p->sw = (p->sh * (p->tx1 - p->tx0 + 1)) / (p->ty1 - p->ty0 + 1);
	if (p->sw < 1)
		p->sw = 1;
}

static void	setup_sprite_window(t_app *app, t_sprite_proj *p)
{
	p->x0 = p->sx - p->sw / 2;
	p->x1 = p->sx + p->sw / 2;
	p->y1 = app->frame.height / 2 + (int)(p->sh * BONUS_SPRITE_FLOOR_OFFSET);
	p->y0 = p->y1 - p->sh;
	if (p->y0 < 0)
		p->y0 = 0;
	if (p->y1 > app->frame.height)
		p->y1 = app->frame.height;
}

int	bonus_setup_sprite_projection(t_app *app, int i,
	t_sprite_proj *p, t_img **tex)
{
	if (setup_sprite_camera(app, i, p))
		return (1);
	*tex = bonus_pick_sprite_texture(app, app->bonus.sprites.types[i]);
	bonus_sprite_setup_bounds(*tex, p);
	setup_sprite_size(app, i, p, *tex);
	setup_sprite_window(app, p);
	return (0);
}
