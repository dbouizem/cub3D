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

void	bonus_sprites_rebuild(t_app *app)
{
	if (!app || !app->map.grid)
		return ;
	app->bonus.sprites.count = 0;
	if (bonus_sprite_ensure_cap(&app->bonus.sprites,
			bonus_sprite_count_map(app)) != 0)
		return ;
	bonus_sprite_fill_from_map(app);
}

int	bonus_sprites_init(t_app *app)
{
	t_bonus_sprites	*sp;

	if (!app || !app->mlx_ptr || app->win_w <= 0)
		return (1);
	sp = &app->bonus.sprites;
	ft_bzero(sp, sizeof(*sp));
	sp->zbuf = malloc(sizeof(double) * (size_t)app->win_w);
	if (!sp->zbuf)
		return (1);
	sp->zcap = app->win_w;
	if (bonus_sprite_load_tex(app, &sp->star_tex, BONUS_SPRITE_STAR_XPM) != 0)
		return (bonus_sprites_shutdown(app), 1);
	if (bonus_sprite_load_tex(app, &sp->at_tex, BONUS_SPRITE_AT_XPM) != 0)
		return (bonus_sprites_shutdown(app), 1);
	bonus_sprites_rebuild(app);
	return (0);
}

void	bonus_sprites_shutdown(t_app *app)
{
	t_bonus_sprites	*sp;

	if (!app)
		return ;
	sp = &app->bonus.sprites;
	bonus_sprite_destroy_tex(app, &sp->star_tex);
	bonus_sprite_destroy_tex(app, &sp->at_tex);
	free(sp->zbuf);
	free(sp->xs);
	free(sp->ys);
	free(sp->types);
	free(sp->dists);
	ft_bzero(sp, sizeof(*sp));
}

void	bonus_sprites_set_depth(t_app *app, int x, double dist)
{
	if (!app || !app->bonus.sprites.zbuf)
		return ;
	if (x < 0 || x >= app->bonus.sprites.zcap)
		return ;
	app->bonus.sprites.zbuf[x] = dist;
}
