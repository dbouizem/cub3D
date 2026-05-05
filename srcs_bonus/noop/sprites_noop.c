/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_noop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 10:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/10 10:55:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Sprite storage and textures are not initialized in mandatory mode.
*/
int	bonus_sprites_init(t_app *app)
{
	(void)app;
	return (0);
}

/*
** Mandatory mode has no sprite allocations to release.
*/
void	bonus_sprites_shutdown(t_app *app)
{
	(void)app;
}

/*
** Rebuilding the sprite list is a no-op without bonus sprites.
*/
int	bonus_sprites_rebuild(t_app *app)
{
	(void)app;
	return (0);
}

/*
** The depth buffer is only needed by bonus sprite rendering.
*/
int	bonus_sprites_resize_zbuf(t_app *app, int width)
{
	(void)app;
	(void)width;
	return (0);
}

/*
** Mandatory raycasting does not store per-column sprite depth.
*/
void	bonus_sprites_set_depth(t_app *app, int x, double dist)
{
	(void)app;
	(void)x;
	(void)dist;
}
