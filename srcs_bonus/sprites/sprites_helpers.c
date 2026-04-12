/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/10 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bonus_sprite_destroy_tex(t_app *app, t_img *img)
{
	if (app->mlx_ptr && img->img_ptr)
		mlx_destroy_image(app->mlx_ptr, img->img_ptr);
	img->img_ptr = NULL;
	img->addr = NULL;
}

static int	fail_bonus_texture(const char *prefix, const char *path)
{
	char	*msg;

	msg = ft_strjoin3(prefix, path, "\n");
	if (msg)
		error_put(msg);
	else
		error_put("Error\nFailed to load bonus texture\n");
	free(msg);
	return (1);
}

static int	load_xpm_data(t_app *app, t_img *img, const char *path,
	char *resolved)
{
	img->img_ptr = mlx_xpm_file_to_image(app->mlx_ptr, resolved,
			&img->width, &img->height);
	free(resolved);
	if (!img->img_ptr)
		return (fail_bonus_texture("Error\nFailed to load bonus texture: ",
				path));
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
		return (error_put("Error\nFailed to access bonus texture data\n"),
			bonus_sprite_destroy_tex(app, img), 1);
	return (0);
}

int	bonus_sprite_load_tex(t_app *app, t_img *img, const char *path)
{
	char	*resolved;

	resolved = bonus_resolve_asset_path(app, path);
	if (!resolved)
		return (fail_bonus_texture(
				"Error\nFailed to resolve bonus texture: ", path));
	return (load_xpm_data(app, img, path, resolved));
}
