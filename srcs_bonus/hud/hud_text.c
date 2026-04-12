/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	bonus_label_width(const char *text, int scale)
{
	return ((int)ft_strlen(text) * (scale * 4) - scale);
}

int	bonus_number_width(int digits, int scale)
{
	return (digits * (scale * 4) - scale);
}

void	bonus_draw_label(t_img *img, t_hud_text txt, const char *text)
{
	int	i;

	i = 0;
	while (text[i])
	{
		bonus_draw_label_glyph(img, (t_hud_text){txt.x + i
			* (txt.scale * 4), txt.y, txt.color, txt.scale}, text[i]);
		i++;
	}
}

void	bonus_draw_number(t_img *img, t_hud_text txt, int value, int digits)
{
	int	div;
	int	i;

	if (value < 0)
		value = 0;
	div = 1;
	i = 1;
	while (i++ < digits)
		div *= 10;
	i = 0;
	while (i < digits)
	{
		bonus_draw_digit(img, (t_hud_text){txt.x + i * (txt.scale * 4),
			txt.y, txt.color, txt.scale}, (value / div) % 10);
		div /= 10;
		i++;
	}
}
