/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeceiro <bbeceiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:28:35 by bbeceiro          #+#    #+#             */
/*   Updated: 2026/05/07 14:28:37 by bbeceiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_one_texture(t_app *app, char *path, t_img *tex, char *name)
{
	int	w;
	int	h;

	tex->img_ptr = mlx_xpm_file_to_image(app->mlx_ptr, path, &w, &h);
	if (!tex->img_ptr)
	{
		ft_putstr_fd("Error\nFailed to load texture: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
	{
		ft_putstr_fd("Error\nFailed to access texture data: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	tex->width = w;
	tex->height = h;
	return (0);
}

int	load_textures(t_app *app)
{
	if (load_one_texture(app, app->config.tex_no, &app->tex_no, "North") != 0)
		return (1);
	if (load_one_texture(app, app->config.tex_so, &app->tex_so, "South") != 0)
		return (1);
	if (load_one_texture(app, app->config.tex_we, &app->tex_we, "West") != 0)
		return (1);
	if (load_one_texture(app, app->config.tex_ea, &app->tex_ea, "East") != 0)
		return (1);
	return (0);
}
