/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_anim_pick.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 09:15:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/08 09:15:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*pick_from_frames(t_img *frames, int count, int base)
{
	int	i;
	int	j;

	j = 0;
	while (j < count)
	{
		i = (base + j) % count;
		if (frames[i].img_ptr && frames[i].addr)
			return (&frames[i]);
		j++;
	}
	return (NULL);
}

static t_img	*pick_anim(t_app *app, t_img *frames, int count, double fps)
{
	int	base;

	base = (int)((double)app->frame_count * fps / 60.0);
	return (pick_from_frames(frames, count, base));
}

t_img	*bonus_pick_anim_texture(t_app *app, char tile)
{
	if (tile == 'o')
		return (pick_anim(app, app->bonus_wall_o_anim,
				BONUS_ANIM_O_FRAMES, BONUS_ANIM_O_FPS));
	if (tile == 'p')
		return (pick_anim(app, app->bonus_wall_p_anim,
				BONUS_ANIM_P_FRAMES, BONUS_ANIM_P_FPS));
	if (tile == 'q')
		return (pick_anim(app, app->bonus_wall_q_anim,
				BONUS_ANIM_Q_FRAMES, BONUS_ANIM_Q_FPS));
	if (tile == '*')
		return (pick_anim(app, app->bonus_wall_star_anim,
				BONUS_ANIM_STAR_FRAMES, BONUS_ANIM_STAR_FPS));
	if (tile == '.')
		return (pick_anim(app, app->bonus_wall_dot_anim,
				BONUS_ANIM_DOT_FRAMES, BONUS_ANIM_DOT_FPS));
	if (tile == '(')
		return (pick_anim(app, app->bonus_wall_lparen_anim,
				BONUS_ANIM_LPAREN_FRAMES, BONUS_ANIM_LPAREN_FPS));
	return (NULL);
}
