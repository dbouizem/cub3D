/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/08 09:55:26 by brrr1            ###   ########.fr       */
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

static void	draw_player_square(t_img *img, int x, int y, int color)
{
	int	y_offset;
	int	x_offset;

	y_offset = -5;
	while (y_offset <= 5)
	{
		x_offset = -5;
		while (x_offset <= 5)
		{
			put_pixel(img, x + x_offset, y + y_offset, color);
			x_offset++;
		}
		y_offset++;
	}
}

static void	draw_player(t_app *app, t_img *img)
{
	double	scale_x;
	double	scale_y;
	int		screen_x;
	int		screen_y;
	int		player_color;

	if (app->map_width == 0 || app->map_height == 0)
		return ;
	scale_x = (double)app->win_w / (double)app->map_width;
	scale_y = (double)app->win_h / (double)app->map_height;
	screen_x = (int)(app->player_x * scale_x);
	screen_y = (int)(app->player_y * scale_y);
	player_color = (255 << 16);
	draw_player_square(img, screen_x, screen_y, player_color);
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
