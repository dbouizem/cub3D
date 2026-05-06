/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_api_noop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:42:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 14:42:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Door state is not allocated in mandatory mode.
*/
int	bonus_doors_init(t_app *app)
{
	(void)app;
	return (0);
}

/*
** Mandatory mode has no animated doors to update each frame.
*/
void	bonus_doors_update(t_app *app)
{
	(void)app;
}

/*
** Mandatory mode has no door array to free.
*/
void	bonus_doors_shutdown(t_app *app)
{
	(void)app;
}

/*
** No tile is considered a door in mandatory mode.
*/
int	bonus_is_door_tile(char c)
{
	(void)c;
	return (0);
}
