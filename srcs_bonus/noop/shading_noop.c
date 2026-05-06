/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading_noop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 16:10:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/05/06 16:10:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Mandatory floor and ceiling keep their original RGB color.
*/
int	apply_flat_shading(int color, int y, int height)
{
	(void)y;
	(void)height;
	return (color);
}

/*
** Mandatory wall textures keep their original colors.
*/
int	apply_wall_shading(int color, t_ray ray)
{
	(void)ray;
	return (color);
}
