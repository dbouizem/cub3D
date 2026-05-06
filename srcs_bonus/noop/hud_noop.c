/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_noop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:46:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/05/06 16:20:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** HUD assets are not loaded for the mandatory build.
*/
int	bonus_hud_init(t_app *app)
{
	(void)app;
	return (0);
}

/*
** Mandatory mode has no HUD images to destroy.
*/
void	bonus_hud_shutdown(t_app *app)
{
	(void)app;
}

/*
** No HUD animation/state update is needed in mandatory mode.
*/
void	bonus_hud_update(t_app *app)
{
	(void)app;
}

/*
** Mouse fire has no effect without the bonus weapon/HUD system.
*/
int	bonus_hud_try_fire(t_app *app)
{
	(void)app;
	return (0);
}

/*
** Mandatory mode draws only the world, with no HUD overlay.
*/
void	bonus_draw_hud(t_app *app)
{
	(void)app;
}
