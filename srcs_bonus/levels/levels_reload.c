/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_reload.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 22:15:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 22:15:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_img_local(t_app *app, t_img *img)
{
	if (app->mlx_ptr && img->img_ptr)
		mlx_destroy_image(app->mlx_ptr, img->img_ptr);
	img->img_ptr = NULL;
	img->addr = NULL;
}

static void	free_level_data(t_app *app)
{
	bonus_doors_shutdown(app);
	destroy_img_local(app, &app->tex_no);
	destroy_img_local(app, &app->tex_so);
	destroy_img_local(app, &app->tex_we);
	destroy_img_local(app, &app->tex_ea);
	free(app->config.tex_no);
	free(app->config.tex_so);
	free(app->config.tex_we);
	free(app->config.tex_ea);
	app->config.tex_no = NULL;
	app->config.tex_so = NULL;
	app->config.tex_we = NULL;
	app->config.tex_ea = NULL;
	free_split(app->map.grid);
	app->map.grid = NULL;
	app->map.height = 0;
}

static int	load_level_textures(t_app *app)
{
	app->tex_no.img_ptr = mlx_xpm_file_to_image(app->mlx_ptr,
			app->config.tex_no, &app->tex_no.width, &app->tex_no.height);
	app->tex_so.img_ptr = mlx_xpm_file_to_image(app->mlx_ptr,
			app->config.tex_so, &app->tex_so.width, &app->tex_so.height);
	app->tex_we.img_ptr = mlx_xpm_file_to_image(app->mlx_ptr,
			app->config.tex_we, &app->tex_we.width, &app->tex_we.height);
	app->tex_ea.img_ptr = mlx_xpm_file_to_image(app->mlx_ptr,
			app->config.tex_ea, &app->tex_ea.width, &app->tex_ea.height);
	if (!app->tex_no.img_ptr || !app->tex_so.img_ptr
		|| !app->tex_we.img_ptr || !app->tex_ea.img_ptr)
		return (error_put("Error\nFailed to load texture\n"), 1);
	app->tex_no.addr = mlx_get_data_addr(app->tex_no.img_ptr, &app->tex_no.bpp,
			&app->tex_no.line_len, &app->tex_no.endian);
	app->tex_so.addr = mlx_get_data_addr(app->tex_so.img_ptr, &app->tex_so.bpp,
			&app->tex_so.line_len, &app->tex_so.endian);
	app->tex_we.addr = mlx_get_data_addr(app->tex_we.img_ptr, &app->tex_we.bpp,
			&app->tex_we.line_len, &app->tex_we.endian);
	app->tex_ea.addr = mlx_get_data_addr(app->tex_ea.img_ptr, &app->tex_ea.bpp,
			&app->tex_ea.line_len, &app->tex_ea.endian);
	if (!app->tex_no.addr || !app->tex_so.addr || !app->tex_we.addr
		|| !app->tex_ea.addr)
		return (error_put("Error\nFailed to access texture data\n"), 1);
	return (0);
}

static int	apply_next_level(t_app *app, t_app *next)
{
	free_level_data(app);
	app->config = next->config;
	app->map = next->map;
	app->player = next->player;
	next->config.tex_no = NULL;
	next->config.tex_so = NULL;
	next->config.tex_we = NULL;
	next->config.tex_ea = NULL;
	next->map.grid = NULL;
	next->map.height = 0;
	app->ceiling_color = (app->config.ceiling_rgb[0] << 16)
		| (app->config.ceiling_rgb[1] << 8) | app->config.ceiling_rgb[2];
	app->floor_color = (app->config.floor_rgb[0] << 16)
		| (app->config.floor_rgb[1] << 8) | app->config.floor_rgb[2];
	if (load_level_textures(app) != 0)
		return (1);
	if (bonus_doors_init(app) != 0)
		return (1);
	init_player_vectors(app);
	ft_bzero(&app->input, sizeof(app->input));
	return (0);
}

int	bonus_load_next_level(t_app *app)
{
	t_app			next;
	t_bonus_levels	*levels;
	int				next_i;

	if (!app)
		return (1);
	levels = &app->bonus.levels;
	if (!levels->active || levels->current + 1 >= levels->count)
		return (1);
	next_i = levels->current + 1;
	init_app(&next);
	if (parse_file(&next, levels->paths[next_i]) != 0)
		return (free_app(&next), 1);
	if (apply_next_level(app, &next) != 0)
		return (free_app(&next), 1);
	free_app(&next);
	levels->current = next_i;
	return (0);
}
