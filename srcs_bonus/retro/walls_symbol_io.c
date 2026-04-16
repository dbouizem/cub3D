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
	const char	*map[BONUS_WALL_SYMBOL_COUNT] = {
		BONUS_WALL_EXCL_XPM, BONUS_WALL_DQUOTE_XPM, BONUS_WALL_HASH_XPM,
		BONUS_WALL_DOLLAR_XPM, BONUS_WALL_PERCENT_XPM, BONUS_WALL_AMP_XPM,
		BONUS_WALL_SQUOTE_XPM, BONUS_WALL_LPAREN_XPM, BONUS_WALL_RPAREN_XPM,
		BONUS_WALL_STAR_XPM, BONUS_WALL_PLUS_XPM, BONUS_WALL_COMMA_XPM,
		BONUS_WALL_MINUS_XPM, BONUS_WALL_DOT_XPM, BONUS_WALL_SLASH_XPM,
		BONUS_WALL_COLON_XPM, BONUS_WALL_SEMI_XPM, BONUS_WALL_LT_XPM,
		BONUS_WALL_EQ_XPM, BONUS_WALL_GT_XPM, BONUS_WALL_QMARK_XPM,
		BONUS_WALL_AT_XPM, BONUS_WALL_LBRACK_XPM, BONUS_WALL_BSLASH_XPM,
		BONUS_WALL_RBRACK_XPM, BONUS_WALL_CARET_XPM, BONUS_WALL_UNDERSCORE_XPM,
		BONUS_WALL_BACKTICK_XPM, BONUS_WALL_LBRACE_XPM, BONUS_WALL_PIPE_XPM,
		BONUS_WALL_RBRACE_XPM, BONUS_WALL_TILDE_XPM};
	int			i;

	i = 0;
	while (i < BONUS_WALL_SYMBOL_COUNT)
	{
		paths[i] = map[i];
		i++;
	}
}

static void	warn_symbol_load(const char *path)
{
	error_put("Warning\nBonus symbol texture missing, using wall fallback: ");
	error_put(path);
	error_put("\n");
}

static int	load_symbol_texture(t_app *app, t_img *img, const char *path)
{
	char	*resolved;

	retro_reset_img(img);
	resolved = bonus_resolve_asset_path(app, path);
	if (!resolved)
		return (warn_symbol_load(path), 1);
	img->img_ptr = mlx_xpm_file_to_image(app->mlx_ptr, resolved,
			&img->width, &img->height);
	free(resolved);
	if (img->img_ptr)
		img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
				&img->line_len, &img->endian);
	if (!img->addr)
		return (retro_destroy_img(app, img), warn_symbol_load(path), 1);
	return (0);
}

int	bonus_load_symbol_textures(t_app *app)
{
	int			i;
	int			missing;
	const char	*paths[BONUS_WALL_SYMBOL_COUNT];

	init_symbol_paths(paths);
	i = 0;
	missing = 0;
	while (i < BONUS_WALL_SYMBOL_COUNT)
	{
		missing += load_symbol_texture(app,
				&app->bonus.assets.wall_symbols[i], paths[i]);
		i++;
	}
	return (missing);
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
