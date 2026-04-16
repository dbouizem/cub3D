/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_paths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 10:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/12 10:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	fill_digit_paths(const char **wall_paths)
{
	wall_paths[0] = BONUS_WALL2_XPM;
	wall_paths[1] = BONUS_WALL3_XPM;
	wall_paths[2] = BONUS_WALL4_XPM;
	wall_paths[3] = BONUS_WALL5_XPM;
	wall_paths[4] = BONUS_WALL6_XPM;
	wall_paths[5] = BONUS_WALL7_XPM;
	wall_paths[6] = BONUS_WALL8_XPM;
	wall_paths[7] = BONUS_WALL9_XPM;
}

static void	fill_alpha_paths_one(const char **wall_paths)
{
	wall_paths[8] = BONUS_WALL_A_XPM;
	wall_paths[9] = BONUS_WALL_B_XPM;
	wall_paths[10] = BONUS_WALL_C_XPM;
	wall_paths[11] = BONUS_WALL_D_XPM;
	wall_paths[12] = BONUS_WALL_E_XPM;
	wall_paths[13] = BONUS_WALL_F_XPM;
	wall_paths[14] = BONUS_WALL_G_XPM;
	wall_paths[15] = BONUS_WALL_H_XPM;
	wall_paths[16] = BONUS_WALL_I_XPM;
	wall_paths[17] = BONUS_WALL_J_XPM;
	wall_paths[18] = BONUS_WALL_K_XPM;
	wall_paths[19] = BONUS_WALL_L_XPM;
	wall_paths[20] = BONUS_WALL_M_XPM;
}

static void	fill_alpha_paths_two(const char **wall_paths)
{
	wall_paths[21] = BONUS_WALL_N_XPM;
	wall_paths[22] = BONUS_WALL_O_XPM;
	wall_paths[23] = BONUS_WALL_P_XPM;
	wall_paths[24] = BONUS_WALL_Q_XPM;
	wall_paths[25] = BONUS_WALL_R_XPM;
	wall_paths[26] = BONUS_WALL_S_XPM;
	wall_paths[27] = BONUS_WALL_T_XPM;
	wall_paths[28] = BONUS_WALL_U_XPM;
	wall_paths[29] = BONUS_WALL_V_XPM;
	wall_paths[30] = BONUS_WALL_W_XPM;
	wall_paths[31] = BONUS_WALL_X_XPM;
	wall_paths[32] = BONUS_WALL_Y_XPM;
	wall_paths[33] = BONUS_WALL_Z_XPM;
}

static void	fill_default_paths(const char **paths, int count, const char *def)
{
	int	i;

	i = 0;
	while (i < count)
		paths[i++] = def;
}

void	bonus_init_wall_path_tables(const char **wall_paths,
	const char **door_paths)
{
	fill_default_paths(wall_paths, BONUS_WALL_COUNT, BONUS_WALL_DEFAULT_XPM);
	fill_digit_paths(wall_paths);
	fill_alpha_paths_one(wall_paths);
	fill_alpha_paths_two(wall_paths);
	fill_default_paths(door_paths, BONUS_DOOR_COUNT, BONUS_DOOR_DEFAULT_XPM);
	if (BONUS_DOOR_COUNT > 0)
		door_paths[0] = BONUS_DOOR_A_XPM;
	if (BONUS_DOOR_COUNT > 1)
		door_paths[1] = BONUS_DOOR_D_XPM;
}
