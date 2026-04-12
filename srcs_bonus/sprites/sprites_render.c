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

	tx = p.tx0 + ((x - p.x0) * (p.tx1 - p.tx0 + 1) / p.sw);
	y = p.y0;
	while (y < p.y1)
	{
		ty = p.ty0 + ((y - p.y0) * (p.ty1 - p.ty0 + 1) / p.sh);
		color = retro_get_pixel(tex, tx, ty);
		if (bonus_sprite_is_opaque(color))
			put_pixel(&app->frame, x, y, (int)color);
		y++;
	}
}

static void	draw_one_sprite(t_app *app, int i)
{
	t_sprite_proj	p;
	t_img			*tex;
	int				x;

	if (!app->bonus.sprites.active[i])
		return ;
	if (bonus_setup_sprite_projection(app, i, &p, &tex))
		return ;
	bonus_draw_sprite_shadow(app, p);
	x = p.x0;
	while (x < p.x1)
	{
		if (x >= 0 && x < app->frame.width
			&& p.sy < app->bonus.sprites.zbuf[x])
			draw_stripe(app, p, tex, x);
		x++;
	}
}

void	bonus_draw_sprites(t_app *app)
{
	int	i;

	if (!app || !app->bonus.sprites.zbuf || app->bonus.sprites.count <= 0)
		return ;
	bonus_shift_sprite_space(&app->bonus.sprites, &app->player, -1.0);
	sort_bonus_sprites(&app->bonus.sprites);
	i = -1;
	while (++i < app->bonus.sprites.count)
		draw_one_sprite(app, i);
	bonus_shift_sprite_space(&app->bonus.sprites, &app->player, 1.0);
}
