/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_hud_noop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:46:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/10 15:46:00 by dbouizem         ###   ########.fr       */
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
