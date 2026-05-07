/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeceiro <bbeceiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:30:41 by bbeceiro          #+#    #+#             */
/*   Updated: 2026/05/07 14:30:42 by bbeceiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	draw_frame(t_app *app)
{
	handle_movement(app);
	handle_rotation(app);
	clear_frame(app);
	render_rays(app);
	mlx_put_image_to_window(app->mlx_ptr, app->win_ptr,
		app->frame.img_ptr, 0, 0);
	return (0);
}
