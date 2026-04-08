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

int	bonus_is_valid_map_char(char c)
{
	(void)c;
	return (0);
}

int	bonus_is_solid_tile(char c)
{
	return (c == '1');
}

int	bonus_load_wall_textures(t_app *app)
{
	(void)app;
	return (0);
}

void	bonus_destroy_wall_textures(t_app *app)
{
	(void)app;
}

t_img	*bonus_pick_wall_texture(t_app *app, char tile)
{
	(void)app;
	(void)tile;
	return (NULL);
}
