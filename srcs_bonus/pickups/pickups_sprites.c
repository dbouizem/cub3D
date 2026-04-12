/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickups_sprites.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:05:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 19:05:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bonus_pickups_count_active(t_app *app)
{
	int	i;
	int	count;

	if (!app)
		return (0);
	i = 0;
	count = 0;
	while (i < app->bonus.pickups.count)
	{
		if (!app->bonus.pickups.items[i].collected)
			count++;
		i++;
	}
	return (count);
}

static void	fill_one_active_sprite(t_app *app, t_pickup *pickup, int *j)
{
	app->bonus.sprites.types[*j] = pickup->type;
	app->bonus.sprites.xs[*j] = pickup->x;
	app->bonus.sprites.ys[*j] = pickup->y;
	app->bonus.sprites.active[*j] = 1;
	(*j)++;
}

void	bonus_pickups_fill_active_sprites(t_app *app)
{
	int			i;
	int			j;
	t_pickup	*pickup;

	i = 0;
	j = 0;
	while (i < app->bonus.pickups.count)
	{
		pickup = &app->bonus.pickups.items[i];
		if (!pickup->collected)
			fill_one_active_sprite(app, pickup, &j);
		i++;
	}
	app->bonus.sprites.count = j;
}
