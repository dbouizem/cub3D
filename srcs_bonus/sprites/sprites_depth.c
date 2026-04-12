/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_depth.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:50:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 18:50:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bonus_sprites_resize_zbuf(t_app *app, int width)
{
	t_bonus_sprites	*sp;
	double			*new_zbuf;

	if (!app || width <= 0)
		return (1);
	sp = &app->bonus.sprites;
	if (width <= sp->zcap)
		return (0);
	new_zbuf = malloc(sizeof(double) * (size_t)width);
	if (!new_zbuf)
		return (1);
	free(sp->zbuf);
	sp->zbuf = new_zbuf;
	sp->zcap = width;
	return (0);
}

void	bonus_sprites_set_depth(t_app *app, int x, double dist)
{
	if (!app || !app->bonus.sprites.zbuf)
		return ;
	if (x < 0 || x >= app->bonus.sprites.zcap)
		return ;
	app->bonus.sprites.zbuf[x] = dist;
}
