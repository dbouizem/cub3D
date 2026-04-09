/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:20:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/08 11:20:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_img_list(t_app *app, t_img *imgs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		retro_destroy_img(app, &imgs[i]);
		i++;
	}
}

static void	destroy_anim_lists(t_app *app)
{
	destroy_img_list(app, app->bonus.assets.wall_o_anim, BONUS_ANIM_O_FRAMES);
	destroy_img_list(app, app->bonus.assets.wall_p_anim, BONUS_ANIM_P_FRAMES);
	destroy_img_list(app, app->bonus.assets.wall_q_anim, BONUS_ANIM_Q_FRAMES);
	destroy_img_list(app, app->bonus.assets.wall_star_anim,
		BONUS_ANIM_STAR_FRAMES);
	destroy_img_list(app, app->bonus.assets.wall_dot_anim,
		BONUS_ANIM_DOT_FRAMES);
	destroy_img_list(app, app->bonus.assets.wall_lparen_anim,
		BONUS_ANIM_LPAREN_FRAMES);
}

void	bonus_destroy_wall_textures(t_app *app)
{
	destroy_img_list(app, app->bonus.assets.walls, BONUS_WALL_COUNT);
	destroy_img_list(app, app->bonus.assets.doors, BONUS_DOOR_COUNT);
	bonus_destroy_symbol_textures(app);
	destroy_anim_lists(app);
}
