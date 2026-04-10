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

static const char	*g_symbol_paths[BONUS_WALL_SYMBOL_COUNT] = {
	BONUS_WALL_EXCL_XPM, BONUS_WALL_DQUOTE_XPM, BONUS_WALL_HASH_XPM,
	BONUS_WALL_DOLLAR_XPM, BONUS_WALL_PERCENT_XPM, BONUS_WALL_AMP_XPM,
	BONUS_WALL_SQUOTE_XPM, BONUS_WALL_PLUS_XPM, BONUS_WALL_MINUS_XPM,
	BONUS_WALL_COMMA_XPM, BONUS_WALL_DOT_XPM, BONUS_WALL_LPAREN_XPM
};

void	bonus_load_symbol_textures(t_app *app)
{
	int		i;
	t_img	*img;

	i = 0;
	while (i < BONUS_WALL_SYMBOL_COUNT)
	{
		img = &app->bonus.assets.wall_symbols[i];
		retro_reset_img(img);
		img->img_ptr = mlx_xpm_file_to_image(app->mlx_ptr,
				(char *)g_symbol_paths[i], &img->width, &img->height);
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
