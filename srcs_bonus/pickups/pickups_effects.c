/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickups_effects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:05:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 19:05:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	clamp_stat(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

static void	apply_pickup(t_app *app, char type)
{
	if (type == '*')
		app->bonus.stats.hp = clamp_stat(app->bonus.stats.hp
				+ BONUS_PICKUP_HP_GAIN, 0, BONUS_HP_MAX);
	else if (type == '@')
		app->bonus.stats.ammo = clamp_stat(app->bonus.stats.ammo
				+ BONUS_PICKUP_AMMO_GAIN, 0, BONUS_AMMO_MAX);
	else if (type == ')')
		app->bonus.stats.armor = clamp_stat(app->bonus.stats.armor
				+ BONUS_PICKUP_ARMOR_GAIN, 0, BONUS_ARMOR_MAX);
	else if (type == '/')
		app->bonus.stats.score = clamp_stat(app->bonus.stats.score
				+ BONUS_PICKUP_SCORE_GAIN, 0, BONUS_SCORE_MAX);
}

void	bonus_apply_damage(t_app *app, int damage)
{
	int	absorbed;

	if (!app || damage <= 0 || app->bonus.stats.hp <= 0)
		return ;
	if (app->bonus.stats.armor > 0)
	{
		absorbed = damage;
		if (absorbed > app->bonus.stats.armor)
			absorbed = app->bonus.stats.armor;
		app->bonus.stats.armor -= absorbed;
		damage -= absorbed;
	}
	if (damage > 0)
		app->bonus.stats.hp = clamp_stat(app->bonus.stats.hp - damage, 0,
				BONUS_HP_MAX);
	app->bonus.hud.face_react = 1;
	app->bonus.hud.face_react_timer = BONUS_HUD_FACE_REACT_TIME;
}

int	bonus_pickup_collect(t_app *app, t_pickup *pickup)
{
	if (!app || !pickup || pickup->collected)
		return (0);
	apply_pickup(app, pickup->type);
	pickup->collected = 1;
	return (1);
}
