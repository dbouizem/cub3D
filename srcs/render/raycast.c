/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 05:20:00 by brrr1            #+#    #+#             */
/*   Updated: 2026/04/05 05:20:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	raycast_scene(t_app *app)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < app->frame.width)
	{
		ray = cast_ray(app, x);
		draw_wall_column(app, ray);
		x++;
	}
	return (0);
}
