/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_alloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 18:40:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_sprite_arrays(t_bonus_sprites *sp)
{
	free(sp->xs);
	free(sp->ys);
	free(sp->types);
	free(sp->active);
	free(sp->dists);
}

static int	alloc_sprite_arrays(t_bonus_sprites *tmp, int cap)
{
	tmp->xs = malloc(sizeof(double) * (size_t)cap);
	tmp->ys = malloc(sizeof(double) * (size_t)cap);
	tmp->types = malloc(sizeof(char) * (size_t)cap);
	tmp->active = malloc(sizeof(char) * (size_t)cap);
	tmp->dists = malloc(sizeof(double) * (size_t)cap);
	if (!tmp->xs || !tmp->ys || !tmp->types || !tmp->active || !tmp->dists)
		return (free_sprite_arrays(tmp), 1);
	return (0);
}

static void	install_sprite_arrays(t_bonus_sprites *sp, t_bonus_sprites *tmp,
	int cap)
{
	free_sprite_arrays(sp);
	sp->xs = tmp->xs;
	sp->ys = tmp->ys;
	sp->types = tmp->types;
	sp->active = tmp->active;
	sp->dists = tmp->dists;
	sp->cap = cap;
}

int	bonus_sprite_ensure_cap(t_bonus_sprites *sp, int cap)
{
	t_bonus_sprites	tmp;

	if (cap <= sp->cap)
		return (0);
	ft_bzero(&tmp, sizeof(tmp));
	if (alloc_sprite_arrays(&tmp, cap) != 0)
		return (1);
	install_sprite_arrays(sp, &tmp, cap);
	return (0);
}
