/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/12 00:00:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_wall_color(t_ray *ray)
{
	if (ray->side == 0)
		return (0x00CC6666);
	return (0x00884444);
}

void	draw_wall_column(t_app *app, t_ray *ray, int x)
{
	int	y;
	int	color;

	color = get_wall_color(ray);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		put_pixel(&app->frame, x, y, color);
		y++;
	}
}

void	render_rays(t_app *app)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < app->win_w)
	{
		init_ray(app, &ray, x);
		prepare_dda(app, &ray);
		trace_ray(app, &ray);
		draw_wall_column(app, &ray, x);
		x++;
	}
}
