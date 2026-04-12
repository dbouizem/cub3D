/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/12 00:00:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr || x < 0 || y < 0
		|| x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

void	clear_frame(t_app *app)
{
	int	x;
	int	y;

	y = 0;
	while (y < app->win_h)
	{
		x = 0;
		while (x < app->win_w)
		{
			if (y < app->win_h / 2)
				put_pixel(&app->frame, x, y, app->ceiling_color);
			else
				put_pixel(&app->frame, x, y, app->floor_color);
			x++;
		}
		y++;
	}
}

char	get_map_cell(t_app *app, int map_x, int map_y)
{
	int	row_len;

	if (map_y < 0 || map_y >= app->map_height)
		return (' ');
	row_len = ft_strlen(app->file_lines[app->map_start + map_y]);
	if (map_x < 0 || map_x >= row_len)
		return (' ');
	return (app->file_lines[app->map_start + map_y][map_x]);
}
