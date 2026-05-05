/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_noop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:10:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/07 10:10:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Mandatory accepts only standard map characters, so every bonus wall
** symbol is rejected.
*/
int	bonus_is_valid_map_char(char c)
{
	(void)c;
	return (0);
}

/*
** In mandatory mode, only '1' is a blocking wall.
*/
int	bonus_is_solid_tile(char c)
{
	return (c == '1');
}

/*
** Bonus wall texture banks are not loaded by the mandatory build.
*/
int	bonus_load_wall_textures(t_app *app)
{
	(void)app;
	return (0);
}

/*
** Nothing was loaded for bonus walls, so there is nothing to destroy.
*/
void	bonus_destroy_wall_textures(t_app *app)
{
	(void)app;
}

/*
** Mandatory rendering always falls back to NO/SO/WE/EA textures.
*/
t_img	*bonus_pick_wall_texture(t_app *app, char tile)
{
	(void)app;
	(void)tile;
	return (NULL);
}
