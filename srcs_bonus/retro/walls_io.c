/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 10:10:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/07 10:10:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_optional_xpm(t_app *app, t_img *img, const char *path)
{
	char	*resolved;

	retro_reset_img(img);
	resolved = bonus_resolve_asset_path(app, path);
	if (!resolved)
		return ;
	img->img_ptr = mlx_xpm_file_to_image(app->mlx_ptr, resolved,
			&img->width, &img->height);
	free(resolved);
	if (img->img_ptr)
		img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
				&img->line_len, &img->endian);
	if (!img->addr)
		retro_destroy_img(app, img);
}

static void	load_img_list(t_app *app, t_img *imgs,
	const char **paths, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		load_optional_xpm(app, &imgs[i], paths[i]);
		i++;
	}
}

int	bonus_load_wall_textures(t_app *app)
{
	const char	*wall_paths[BONUS_WALL_COUNT];
	const char	*door_paths[BONUS_DOOR_COUNT];

	bonus_init_wall_path_tables(wall_paths, door_paths);
	load_img_list(app, app->bonus.assets.walls, wall_paths, BONUS_WALL_COUNT);
	load_img_list(app, app->bonus.assets.doors, door_paths, BONUS_DOOR_COUNT);
	bonus_load_symbol_textures(app);
	bonus_load_wall_anim_textures(app);
	return (0);
}
