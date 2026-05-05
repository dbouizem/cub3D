/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_query_noop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:43:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 14:43:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Interact key has no door action in mandatory mode.
*/
int	bonus_door_try_toggle(t_app *app)
{
	(void)app;
	return (0);
}

/*
** There are no open doors in mandatory mode.
*/
int	bonus_door_is_open_at(t_app *app, int x, int y)
{
	(void)app;
	(void)x;
	(void)y;
	return (0);
}

/*
** Door collision is disabled in mandatory mode.
*/
int	bonus_door_is_blocking(t_app *app, double px, double py)
{
	(void)app;
	(void)px;
	(void)py;
	return (0);
}

/*
** Door animation progress is always zero without bonus doors.
*/
double	bonus_door_open_progress_at(t_app *app, int x, int y)
{
	(void)app;
	(void)x;
	(void)y;
	return (0.0);
}

/*
** The default inactive state is closed.
*/
int	bonus_door_state_at(t_app *app, int x, int y)
{
	(void)app;
	(void)x;
	(void)y;
	return (DOOR_CLOSED);
}
