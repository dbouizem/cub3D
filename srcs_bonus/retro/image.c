/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/06 11:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	retro_reset_img(t_img *img)
{
	img->img_ptr = NULL;
	img->addr = NULL;
	img->width = 0;
	img->height = 0;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
}

void	retro_destroy_img(t_app *app, t_img *img)
{
	if (app->mlx_ptr && img->img_ptr)
		mlx_destroy_image(app->mlx_ptr, img->img_ptr);
	retro_reset_img(img);
}

int	retro_init_img(t_app *app, t_img *img, int width, int height)
{
	if (!app || !app->mlx_ptr || !img || width <= 0 || height <= 0)
		return (1);
	img->img_ptr = mlx_new_image(app->mlx_ptr, width, height);
	if (!img->img_ptr)
		return (1);
	img->width = width;
	img->height = height;
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->addr || img->bpp < 8 || img->line_len <= 0)
		return (retro_destroy_img(app, img), 1);
	return (0);
}

unsigned int	retro_get_pixel(t_img *img, int x, int y)
{
	char	*src;

	if (!img->addr || x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0);
	src = img->addr + (y * img->line_len + x * (img->bpp / 8));
	return (*(unsigned int *)src);
}
