/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:15:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 19:15:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bonus_destroy_level_tex(t_app *app, t_img *img)
{
	if (app->mlx_ptr && img->img_ptr)
		mlx_destroy_image(app->mlx_ptr, img->img_ptr);
	img->img_ptr = NULL;
	img->addr = NULL;
}

static int	load_one_level_texture(t_app *app, t_img *img, char *path)
{
	img->img_ptr = mlx_xpm_file_to_image(app->mlx_ptr, path,
			&img->width, &img->height);
	if (!img->img_ptr)
		return (error_put("Error\nFailed to load texture\n"), 1);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
		return (error_put("Error\nFailed to access texture data\n"),
			bonus_destroy_level_tex(app, img), 1);
	return (0);
}

int	bonus_load_next_level_textures(t_app *app, t_app *next, t_img tex[4])
{
	if (load_one_level_texture(app, &tex[0], next->config.tex_no) != 0)
		return (1);
	if (load_one_level_texture(app, &tex[1], next->config.tex_so) != 0)
		return (bonus_destroy_level_tex(app, &tex[0]), 1);
	if (load_one_level_texture(app, &tex[2], next->config.tex_we) != 0)
		return (bonus_destroy_level_tex(app, &tex[0]),
			bonus_destroy_level_tex(app, &tex[1]), 1);
	if (load_one_level_texture(app, &tex[3], next->config.tex_ea) != 0)
		return (bonus_destroy_level_tex(app, &tex[0]),
			bonus_destroy_level_tex(app, &tex[1]),
			bonus_destroy_level_tex(app, &tex[2]), 1);
	return (0);
}
