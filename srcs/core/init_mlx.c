/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 10:03:22 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	rgb_to_int(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

int	init_mlx(t_app *app)
{
	app->mlx_ptr = mlx_init();
	if (!app->mlx_ptr)
		return (error_put("Error\nmlx_init failed\n"), 1);
	app->win_ptr = mlx_new_window(app->mlx_ptr, app->win_w,
			app->win_h, "cub3D");
	if (!app->win_ptr)
		return (error_put("Error\nmlx_new_window failed\n"), 1);
	mlx_hook(app->win_ptr, EVENT_KEYRELEASE, 1L << 1, key_release, app);
	app->frame.img_ptr = mlx_new_image(app->mlx_ptr, app->win_w, app->win_h);
	if (!app->frame.img_ptr)
		return (error_put("Error\nmlx_new_image failed\n"), 1);
	app->frame.width = app->win_w;
	app->frame.height = app->win_h;
	app->frame.addr = mlx_get_data_addr(app->frame.img_ptr, &app->frame.bpp,
			&app->frame.line_len, &app->frame.endian);
	if (!app->frame.addr)
		return (error_put("Error\nFailed to access frame buffer\n"), 1);
	app->ceiling_color = rgb_to_int(app->config.ceiling_rgb);
	app->floor_color = rgb_to_int(app->config.floor_rgb);
	if (load_textures(app) != 0)
		return (1);
	return (0);
}
