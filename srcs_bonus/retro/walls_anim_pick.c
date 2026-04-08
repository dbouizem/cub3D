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

t_img	*bonus_pick_anim_texture(t_app *app, char tile)
{
	int	base;

	base = (int)((double)app->frame_count * BONUS_ANIM_O_FPS / 60.0);
	if (tile == 'o')
		return (pick_from_frames(app->bonus_wall_o_anim, BONUS_ANIM_O_FRAMES,
				base));
	base = (int)((double)app->frame_count * BONUS_ANIM_P_FPS / 60.0);
	if (tile == 'p')
		return (pick_from_frames(app->bonus_wall_p_anim, BONUS_ANIM_P_FRAMES,
				base));
	base = (int)((double)app->frame_count * BONUS_ANIM_Q_FPS / 60.0);
	if (tile == 'q')
		return (pick_from_frames(app->bonus_wall_q_anim, BONUS_ANIM_Q_FRAMES,
				base));
	base = (int)((double)app->frame_count * BONUS_ANIM_STAR_FPS / 60.0);
	if (tile == '*')
		return (pick_from_frames(app->bonus_wall_star_anim,
				BONUS_ANIM_STAR_FRAMES, base));
	base = (int)((double)app->frame_count * BONUS_ANIM_LPAREN_FPS / 60.0);
	if (tile == '(')
		return (pick_from_frames(app->bonus_wall_lparen_anim,
				BONUS_ANIM_LPAREN_FRAMES, base));
	return (NULL);
}
