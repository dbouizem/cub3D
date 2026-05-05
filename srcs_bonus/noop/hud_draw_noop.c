/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_draw_noop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 19:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Mouse fire has no effect without the bonus weapon/HUD system.
*/
int	bonus_hud_try_fire(t_app *app)
{
	(void)app;
	return (0);
}

/*
** Pickup animation and collection are disabled in mandatory mode.
*/
void	bonus_pickups_update(t_app *app)
{
	(void)app;
}

/*
** Mandatory mode draws only the world, with no HUD overlay.
*/
void	bonus_draw_hud(t_app *app)
{
	(void)app;
}
