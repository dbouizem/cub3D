/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_symbol_io.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 08:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/08 08:40:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_symbol_paths(const char **paths)
{
	paths[0] = BONUS_WALL_EXCL_XPM;
	paths[1] = BONUS_WALL_DQUOTE_XPM;
	paths[2] = BONUS_WALL_HASH_XPM;
	paths[3] = BONUS_WALL_DOLLAR_XPM;
	paths[4] = BONUS_WALL_PERCENT_XPM;
	paths[5] = BONUS_WALL_AMP_XPM;
	paths[6] = BONUS_WALL_SQUOTE_XPM;
	paths[7] = BONUS_WALL_PLUS_XPM;
	paths[8] = BONUS_WALL_MINUS_XPM;
	paths[9] = BONUS_WALL_COMMA_XPM;
	paths[10] = BONUS_WALL_DOT_XPM;
	paths[11] = BONUS_WALL_LPAREN_XPM;
}

void	bonus_load_symbol_textures(t_app *app)
{
	int			i;
	t_img		*img;
	const char	*paths[BONUS_WALL_SYMBOL_COUNT];

	init_symbol_paths(paths);
	i = 0;
	while (i < BONUS_WALL_SYMBOL_COUNT)
	{
		img = &app->bonus.assets.wall_symbols[i];
		retro_reset_img(img);
		img->img_ptr = mlx_xpm_file_to_image(app->mlx_ptr,
				(char *)paths[i], &img->width, &img->height);
		if (img->img_ptr)
			img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
					&img->line_len, &img->endian);
		if (!img->addr)
			retro_destroy_img(app, img);
		i++;
	}
}

void	bonus_destroy_symbol_textures(t_app *app)
{
	int	i;

	i = 0;
	while (i < BONUS_WALL_SYMBOL_COUNT)
	{
		retro_destroy_img(app, &app->bonus.assets.wall_symbols[i]);
		i++;
	}
}
