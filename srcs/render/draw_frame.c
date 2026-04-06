/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/05 05:20:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (img == NULL || img->addr == NULL)
		return ;
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = (unsigned int)color;
}

static void	draw_background(t_app *app)
{
	int	x;
	int	y;

	y = 0;
	while (y < app->frame.height)
	{
		x = 0;
		while (x < app->frame.width)
		{
			if (y < app->frame.height / 2)
				put_pixel(&app->frame, x, y, app->ceiling_color);
			else
				put_pixel(&app->frame, x, y, app->floor_color);
			x++;
		}
		y++;
	}
}

int	draw_frame(t_app *app)
{
	update_frame_timing(app);
	update_player_input(app);
	draw_background(app);
	raycast_scene(app);
	mlx_put_image_to_window(app->mlx_ptr, app->win_ptr,
		app->frame.img_ptr, 0, 0);
	return (0);
}
