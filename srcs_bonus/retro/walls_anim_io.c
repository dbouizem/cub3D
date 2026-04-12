/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_anim_io.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/12 10:00:00 by dbouizem         ###   ########.fr       */
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

static void	load_three_frame_anims(t_app *app)
{
	const char	*o_paths[3];
	const char	*p_paths[3];
	const char	*q_paths[3];

	o_paths[0] = BONUS_WALL_O1_XPM;
	o_paths[1] = BONUS_WALL_O2_XPM;
	o_paths[2] = BONUS_WALL_O3_XPM;
	p_paths[0] = BONUS_WALL_P1_XPM;
	p_paths[1] = BONUS_WALL_P2_XPM;
	p_paths[2] = BONUS_WALL_P3_XPM;
	q_paths[0] = BONUS_WALL_Q1_XPM;
	q_paths[1] = BONUS_WALL_Q2_XPM;
	q_paths[2] = BONUS_WALL_Q3_XPM;
	load_img_list(app, app->bonus.assets.wall_o_anim, o_paths, 3);
	load_img_list(app, app->bonus.assets.wall_p_anim, p_paths, 3);
	load_img_list(app, app->bonus.assets.wall_q_anim, q_paths, 3);
}

static void	load_four_frame_anims(t_app *app)
{
	const char	*star_paths[4];
	const char	*dot_paths[4];
	const char	*lparen_paths[4];

	star_paths[0] = BONUS_WALL_STAR1_XPM;
	star_paths[1] = BONUS_WALL_STAR2_XPM;
	star_paths[2] = BONUS_WALL_STAR3_XPM;
	star_paths[3] = BONUS_WALL_STAR4_XPM;
	dot_paths[0] = BONUS_WALL_DOT1_XPM;
	dot_paths[1] = BONUS_WALL_DOT2_XPM;
	dot_paths[2] = BONUS_WALL_DOT3_XPM;
	dot_paths[3] = BONUS_WALL_DOT4_XPM;
	lparen_paths[0] = BONUS_WALL_LPAREN1_XPM;
	lparen_paths[1] = BONUS_WALL_LPAREN2_XPM;
	lparen_paths[2] = BONUS_WALL_LPAREN3_XPM;
	lparen_paths[3] = BONUS_WALL_LPAREN4_XPM;
	load_img_list(app, app->bonus.assets.wall_star_anim, star_paths, 4);
	load_img_list(app, app->bonus.assets.wall_dot_anim, dot_paths, 4);
	load_img_list(app, app->bonus.assets.wall_lparen_anim, lparen_paths, 4);
}

void	bonus_load_wall_anim_textures(t_app *app)
{
	load_three_frame_anims(app);
	load_four_frame_anims(app);
}
