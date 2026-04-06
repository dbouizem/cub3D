/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/06 14:27:24 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img || !img->addr || x < 0 || y < 0
		|| x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

static void	draw_player(t_app *app, t_img *img)
{
	double	scale;
	int		screen_x;
	int		screen_y;
	int		player_color;
	int		y_offset;
	int		x_offset;

	scale = app->win_w / 10.0;
	screen_x = (int)(app->player_x * scale);
	screen_y = (int)(app->player_y * scale);
	player_color = (255 << 16);
	y_offset = -5;
	while (y_offset <= 5)
	{
		x_offset = -5;
		while (x_offset <= 5)
		{
			put_pixel(img, screen_x + x_offset, screen_y
				+ y_offset, player_color);
			x_offset++;
		}
		y_offset++;
	}
}

int	draw_frame(t_app *app)
{
	int	x;
	int	y;

	handle_movement(app);
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
	draw_player(app, &app->frame);
	mlx_put_image_to_window(app->mlx_ptr, app->win_ptr,
		app->frame.img_ptr, 0, 0);
	return (0);
}
