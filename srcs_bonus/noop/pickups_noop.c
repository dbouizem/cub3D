/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickups_noop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 18:20:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/10 18:20:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Mandatory maps do not create pickup entities.
*/
int	bonus_pickups_rebuild(t_app *app)
{
	(void)app;
	return (0);
}

/*
** Mandatory mode has no pickup storage to release.
*/
void	bonus_pickups_shutdown(t_app *app)
{
	(void)app;
}

/*
** Pickup animation and collection are disabled in mandatory mode.
*/
void	bonus_pickups_update(t_app *app)
{
	(void)app;
}

/*
** There are no pickups to collect in mandatory mode.
*/
int	bonus_pickup_collect(t_app *app, t_pickup *pickup)
{
	(void)app;
	(void)pickup;
	return (0);
}
