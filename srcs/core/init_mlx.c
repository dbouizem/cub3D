/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/01 14:55:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	rgb_to_int(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

static int	load_texture(t_app *app, t_img *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(app->mlx_ptr, path,
			&tex->width, &tex->height);
	if (!tex->img_ptr)
		return (error_put("Error\nFailed to load texture\n"), 1);
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		return (error_put("Error\nFailed to access texture data\n"), 1);
	return (0);
}

static int	load_textures(t_app *app)
{
	if (load_texture(app, &app->tex_no, app->config.tex_no) != 0)
		return (1);
	if (load_texture(app, &app->tex_so, app->config.tex_so) != 0)
		return (1);
	if (load_texture(app, &app->tex_we, app->config.tex_we) != 0)
		return (1);
	if (load_texture(app, &app->tex_ea, app->config.tex_ea) != 0)
		return (1);
	return (0);
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
	if (bonus_load_wall_textures(app) != 0)
		return (1);
	if (retro_init(app) != 0)
		return (1);
	return (0);
}
