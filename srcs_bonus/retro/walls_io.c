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

static const char	*g_alpha_paths[26] = {
	BONUS_WALL_A_XPM, BONUS_WALL_B_XPM, BONUS_WALL_C_XPM, BONUS_WALL_D_XPM,
	BONUS_WALL_E_XPM, BONUS_WALL_F_XPM, BONUS_WALL_G_XPM, BONUS_WALL_H_XPM,
	BONUS_WALL_I_XPM, BONUS_WALL_J_XPM, BONUS_WALL_K_XPM, BONUS_WALL_L_XPM,
	BONUS_WALL_M_XPM, BONUS_WALL_N_XPM, BONUS_WALL_O_XPM, BONUS_WALL_P_XPM,
	BONUS_WALL_Q_XPM, BONUS_WALL_R_XPM, BONUS_WALL_S_XPM, BONUS_WALL_T_XPM,
	BONUS_WALL_U_XPM, BONUS_WALL_V_XPM, BONUS_WALL_W_XPM, BONUS_WALL_X_XPM,
	BONUS_WALL_Y_XPM, BONUS_WALL_Z_XPM
};

static const char	*g_digit_paths[8] = {
	BONUS_WALL2_XPM, BONUS_WALL3_XPM, BONUS_WALL4_XPM, BONUS_WALL5_XPM,
	BONUS_WALL6_XPM, BONUS_WALL7_XPM, BONUS_WALL8_XPM, BONUS_WALL9_XPM
};

static const char	*g_door_paths[22] = {
	BONUS_DOOR_A_XPM, BONUS_DOOR_B_XPM, BONUS_DOOR_C_XPM, BONUS_DOOR_D_XPM,
	BONUS_DOOR_F_XPM, BONUS_DOOR_G_XPM, BONUS_DOOR_H_XPM, BONUS_DOOR_I_XPM,
	BONUS_DOOR_J_XPM, BONUS_DOOR_K_XPM, BONUS_DOOR_L_XPM, BONUS_DOOR_M_XPM,
	BONUS_DOOR_O_XPM, BONUS_DOOR_P_XPM, BONUS_DOOR_Q_XPM, BONUS_DOOR_R_XPM,
	BONUS_DOOR_T_XPM, BONUS_DOOR_U_XPM, BONUS_DOOR_V_XPM, BONUS_DOOR_X_XPM,
	BONUS_DOOR_Y_XPM, BONUS_DOOR_Z_XPM
};

static const char	*g_wall_o_anim_paths[BONUS_ANIM_O_FRAMES] = {
	BONUS_WALL_O1_XPM,
	BONUS_WALL_O2_XPM,
	BONUS_WALL_O3_XPM
};

static const char	*g_wall_p_anim_paths[BONUS_ANIM_P_FRAMES] = {
	BONUS_WALL_P1_XPM,
	BONUS_WALL_P2_XPM,
	BONUS_WALL_P3_XPM
};

static const char	*g_wall_q_anim_paths[BONUS_ANIM_Q_FRAMES] = {
	BONUS_WALL_Q1_XPM,
	BONUS_WALL_Q2_XPM,
	BONUS_WALL_Q3_XPM
};

static const char	*g_wall_star_anim_paths[BONUS_ANIM_STAR_FRAMES] = {
	BONUS_WALL_STAR1_XPM,
	BONUS_WALL_STAR2_XPM,
	BONUS_WALL_STAR3_XPM,
	BONUS_WALL_STAR4_XPM
};

static const char	*g_wall_lparen_anim_paths[BONUS_ANIM_LPAREN_FRAMES] = {
	BONUS_WALL_LPAREN1_XPM,
	BONUS_WALL_LPAREN2_XPM,
	BONUS_WALL_LPAREN3_XPM,
	BONUS_WALL_LPAREN4_XPM
};

static void	load_optional_xpm(t_app *app, t_img *img, const char *path)
{
	retro_reset_img(img);
	img->img_ptr = mlx_xpm_file_to_image(app->mlx_ptr, (char *)path,
			&img->width, &img->height);
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

static void	init_path_tables(const char **wall_paths, const char **door_paths)
{
	int	i;

	i = 0;
	while (i < BONUS_WALL_COUNT)
		wall_paths[i++] = BONUS_WALL_DEFAULT_XPM;
	i = 0;
	while (i < 8)
	{
		wall_paths[i] = g_digit_paths[i];
		i++;
	}
	while (i < BONUS_WALL_COUNT)
	{
		wall_paths[i] = g_alpha_paths[i - 8];
		i++;
	}
	i = 0;
	while (i < BONUS_DOOR_COUNT)
	{
		door_paths[i] = g_door_paths[i];
		i++;
	}
}

static void	load_anim_lists(t_app *app)
{
	load_img_list(app, app->bonus_wall_o_anim, g_wall_o_anim_paths,
		BONUS_ANIM_O_FRAMES);
	load_img_list(app, app->bonus_wall_p_anim, g_wall_p_anim_paths,
		BONUS_ANIM_P_FRAMES);
	load_img_list(app, app->bonus_wall_q_anim, g_wall_q_anim_paths,
		BONUS_ANIM_Q_FRAMES);
	load_img_list(app, app->bonus_wall_star_anim, g_wall_star_anim_paths,
		BONUS_ANIM_STAR_FRAMES);
	load_img_list(app, app->bonus_wall_lparen_anim, g_wall_lparen_anim_paths,
		BONUS_ANIM_LPAREN_FRAMES);
}

int	bonus_load_wall_textures(t_app *app)
{
	const char	*wall_paths[BONUS_WALL_COUNT];
	const char	*door_paths[BONUS_DOOR_COUNT];

	init_path_tables(wall_paths, door_paths);
	load_img_list(app, app->bonus_walls, wall_paths, BONUS_WALL_COUNT);
	load_img_list(app, app->bonus_doors, door_paths, BONUS_DOOR_COUNT);
	bonus_load_symbol_textures(app);
	load_anim_lists(app);
	return (0);
}
