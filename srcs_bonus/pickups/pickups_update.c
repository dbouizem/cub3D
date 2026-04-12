/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickups_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 18:20:00 by Codex             #+#    #+#             */
/*   Updated: 2026/04/10 18:20:00 by Codex            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_pickup_animation(t_app *app)
{
	t_bonus_sprites	*sp;

	sp = &app->bonus.sprites;
	sp->anim_timer += app->delta_time;
	while (sp->anim_timer >= BONUS_PICKUP_FRAME_TIME)
	{
		sp->anim_timer -= BONUS_PICKUP_FRAME_TIME;
		sp->anim_frame++;
		if (sp->anim_frame >= BONUS_PICKUP_FRAMES)
			sp->anim_frame = 0;
	}
}

static int	try_collect_pickup(t_app *app, t_pickup *pickup)
{
	double	dx;
	double	dy;
	double	d2;
	double	r2;

	if (pickup->collected)
		return (0);
	dx = pickup->x - app->player.x;
	dy = pickup->y - app->player.y;
	d2 = dx * dx + dy * dy;
	r2 = BONUS_PICKUP_RADIUS * BONUS_PICKUP_RADIUS;
	if (d2 > r2)
		return (0);
	return (bonus_pickup_collect(app, pickup));
}

void	bonus_pickups_update(t_app *app)
{
	int	i;
	int	changed;

	if (!app)
		return ;
	update_pickup_animation(app);
	i = 0;
	changed = 0;
	while (i < app->bonus.pickups.count)
	{
		if (try_collect_pickup(app, &app->bonus.pickups.items[i]))
			changed = 1;
		i++;
	}
	if (changed)
	{
		if (bonus_sprites_rebuild(app) != 0)
			error_put("Error\nFailed to rebuild sprites\n");
	}
}
