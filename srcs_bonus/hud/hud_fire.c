/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_fire.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <dbouizem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/05/07 18:27:16 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_shot_blocker(char cell)
{
	if (cell == '0' || cell == 'N' || cell == 'S'
		|| cell == 'E' || cell == 'W')
		return (0);
	if (bonus_is_sprite_tile(cell))
		return (0);
	if (cell == ' ')
		return (1);
	return (!bonus_is_door_tile(cell));
}

static int	try_hit_pickup(t_app *app, double sx, double sy)
{
	int			i;
	double		dx;
	double		dy;
	double		r2;
	t_pickup	*pickup;

	i = 0;
	r2 = BONUS_WEAPON_HIT_RADIUS * BONUS_WEAPON_HIT_RADIUS;
	while (i < app->bonus.pickups.count)
	{
		pickup = &app->bonus.pickups.items[i];
		if (!pickup->collected)
		{
			dx = pickup->x - sx;
			dy = pickup->y - sy;
			if (dx * dx + dy * dy <= r2)
				return (bonus_pickup_collect(app, pickup));
		}
		i++;
	}
	return (0);
}

static void	handle_weapon_hit(t_app *app, double sx, double sy)
{
	char	cell;

	cell = bonus_map_cell_at(app, (int)floor(sx), (int)floor(sy));
	if (bonus_is_door_tile(cell))
		return ;
}

static void	bonus_weapon_hitscan(t_app *app)
{
	double	dist;
	double	sx;
	double	sy;
	char	cell;

	dist = 0.25;
	while (dist <= BONUS_WEAPON_RANGE)
	{
		sx = app->player.x + app->dir_x * dist;
		sy = app->player.y + app->dir_y * dist;
		if (try_hit_pickup(app, sx, sy))
			return ((void)bonus_sprites_rebuild(app));
		cell = bonus_map_cell_at(app, (int)floor(sx), (int)floor(sy));
		if (bonus_is_door_tile(cell))
			return (handle_weapon_hit(app, sx, sy));
		if (is_shot_blocker(cell))
			return ;
		dist += BONUS_WEAPON_STEP;
	}
}

int	bonus_hud_try_fire(t_app *app)
{
	t_bonus_hud	*hud;

	if (!app)
		return (1);
	hud = &app->bonus.hud;
	if (hud->weapon_cooldown > 0.0 || app->bonus.stats.ammo <= 0)
		return (1);
	app->bonus.stats.ammo--;
	hud->weapon_frame = 1;
	hud->weapon_timer = 0.0;
	hud->weapon_cooldown = BONUS_WEAPON_FIRE_COOLDOWN;
	hud->face_react = 1;
	hud->face_react_timer = BONUS_HUD_FACE_REACT_TIME;
	bonus_weapon_hitscan(app);
	return (0);
}
