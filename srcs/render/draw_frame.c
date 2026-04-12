/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 11:02:13 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
