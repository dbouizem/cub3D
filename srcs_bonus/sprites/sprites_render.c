/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 10:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/10 10:55:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_stripe(t_app *app, t_sprite_proj p, t_img *tex, int x)
{
	int				y;
	int				tx;
	int				ty;
	unsigned int	color;

	tx = (x - p.x0) * tex->width / p.sh;
	y = p.y0;
	while (y < p.y1)
	{
		ty = (y - p.y0) * tex->height / p.sh;
		color = retro_get_pixel(tex, tx, ty);
		if (color != 0xFF000000)
			put_pixel(&app->frame, x, y, (int)color);
		y++;
	}
}

static int	setup_sprite(t_app *app, int i, t_sprite_proj *p, t_img **tex)
{
	double			inv;
	double			tx;

	inv = 1.0 / (app->plane_x * app->dir_y - app->dir_x * app->plane_y);
	tx = inv * (app->dir_y * app->bonus.sprites.xs[i] - app->dir_x
			* app->bonus.sprites.ys[i]);
	p->sy = inv * (-app->plane_y * app->bonus.sprites.xs[i] + app->plane_x
			* app->bonus.sprites.ys[i]);
	if (p->sy <= 0.0)
		return (1);
	p->sx = (int)((app->frame.width / 2) * (1.0 + tx / p->sy));
	p->sh = (int)(app->frame.height / (p->sy + 1e-9));
	if (p->sh < 1)
		p->sh = 1;
	p->x0 = p->sx - p->sh / 2;
	p->x1 = p->sx + p->sh / 2;
	p->y0 = app->frame.height / 2 - p->sh / 2;
	p->y1 = app->frame.height / 2 + p->sh / 2;
	if (app->bonus.sprites.types[i] == '@')
		*tex = &app->bonus.sprites.at_tex;
	else
		*tex = &app->bonus.sprites.star_tex;
	return (0);
}

static void	draw_one_sprite(t_app *app, int i)
{
	t_sprite_proj	p;
	t_img			*tex;
	int				x;

	if (setup_sprite(app, i, &p, &tex))
		return ;
	x = p.x0;
	while (x < p.x1)
	{
		if (x >= 0 && x < app->frame.width
			&& p.sy < app->bonus.sprites.zbuf[x])
			draw_stripe(app, p, tex, x);
		x++;
	}
}

static void	shift_sprite_space(t_bonus_sprites *sp, t_player *pl, double sign)
{
	int	i;

	i = -1;
	while (++i < sp->count)
	{
		sp->xs[i] += pl->x * sign;
		sp->ys[i] += pl->y * sign;
	}
}

void	bonus_draw_sprites(t_app *app)
{
	int	i;

	if (!app || !app->bonus.sprites.zbuf || app->bonus.sprites.count <= 0)
		return ;
	shift_sprite_space(&app->bonus.sprites, &app->player, -1.0);
	sort_bonus_sprites(&app->bonus.sprites);
	i = -1;
	while (++i < app->bonus.sprites.count)
		draw_one_sprite(app, i);
	shift_sprite_space(&app->bonus.sprites, &app->player, 1.0);
}
