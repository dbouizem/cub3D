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

static void	warn_bonus_texture(const char *msg, const char *path)
{
	error_put(msg);
	error_put(path);
	error_put("\n");
}

static int	load_optional_xpm(t_app *app, t_img *img, const char *path)
{
	char	*resolved;

	retro_reset_img(img);
	resolved = bonus_resolve_asset_path(app, path);
	if (!resolved)
		return (warn_bonus_texture("Warning\nBonus texture missing: ",
				path), 1);
	img->img_ptr = mlx_xpm_file_to_image(app->mlx_ptr, resolved,
			&img->width, &img->height);
	free(resolved);
	if (!img->img_ptr)
		return (warn_bonus_texture("Warning\nBonus texture load failed: ",
				path), 1);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->addr)
		return (retro_destroy_img(app, img),
			warn_bonus_texture("Warning\nBonus texture data failed: ",
				path), 1);
	return (0);
}

static int	load_img_list(t_app *app, t_img *imgs,
	const char **paths, int count)
{
	int	i;
	int	missing;

	i = 0;
	missing = 0;
	while (i < count)
	{
		missing += load_optional_xpm(app, &imgs[i], paths[i]);
		i++;
	}
	return (missing);
}

int	bonus_load_wall_textures(t_app *app)
{
	const char	*wall_paths[BONUS_WALL_COUNT];
	const char	*door_paths[BONUS_DOOR_COUNT];
	int			missing;

	bonus_init_wall_path_tables(wall_paths, door_paths);
	missing = 0;
	missing += load_img_list(app, app->bonus.assets.walls,
			wall_paths, BONUS_WALL_COUNT);
	missing += load_img_list(app, app->bonus.assets.doors,
			door_paths, BONUS_DOOR_COUNT);
	missing += bonus_load_symbol_textures(app);
	missing += bonus_load_wall_anim_textures(app);
	if (missing > 0)
		error_put("Warning\nBonus assets incomplete: using fallbacks\n");
	return (0);
}
