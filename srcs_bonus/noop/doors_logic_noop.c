/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_logic_noop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Doors cannot block movement when doors are disabled.
*/
int	bonus_door_blocks_axis(t_app *app, double px, double py, int axis)
{
	(void)app;
	(void)px;
	(void)py;
	(void)axis;
	return (0);
}

/*
** Mandatory raycasts never pass through door panels.
*/
int	bonus_door_allows_passage_at(t_app *app, int x, int y, double hit)
{
	(void)app;
	(void)x;
	(void)y;
	(void)hit;
	return (0);
}

/*
** There is no animated door to check against the player position.
*/
int	bonus_door_is_occupied(t_app *app, t_door *door)
{
	(void)app;
	(void)door;
	return (0);
}
