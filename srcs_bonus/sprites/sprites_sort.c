/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 11:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/10 11:40:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	swap_sprites(t_bonus_sprites *sp, int i, int j)
{
	double	d;
	char	c;

	d = sp->dists[i];
	sp->dists[i] = sp->dists[j];
	sp->dists[j] = d;
	d = sp->xs[i];
	sp->xs[i] = sp->xs[j];
	sp->xs[j] = d;
	d = sp->ys[i];
	sp->ys[i] = sp->ys[j];
	sp->ys[j] = d;
	c = sp->types[i];
	sp->types[i] = sp->types[j];
	sp->types[j] = c;
}

void	sort_bonus_sprites(t_bonus_sprites *sp)
{
	int		i;
	int		j;
	double	dx;
	double	dy;

	i = -1;
	while (++i < sp->count)
	{
		dx = sp->xs[i];
		dy = sp->ys[i];
		sp->dists[i] = dx * dx + dy * dy;
	}
	i = -1;
	while (++i < sp->count)
	{
		j = i;
		while (++j < sp->count)
			if (sp->dists[i] < sp->dists[j])
				swap_sprites(sp, i, j);
	}
}
