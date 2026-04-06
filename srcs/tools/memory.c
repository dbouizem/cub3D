/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:59:59 by dbouizem          #+#    #+#             */
/*   Updated: 2026/03/31 17:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_img(t_app *app, t_img *img)
{
	if (app->mlx_ptr && img->img_ptr)
		mlx_destroy_image(app->mlx_ptr, img->img_ptr);
	img->img_ptr = NULL;
	img->addr = NULL;
}

void	free_split(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	free_app(t_app *app)
{
	free(app->config.tex_no);
	app->config.tex_no = NULL;
	free(app->config.tex_so);
	app->config.tex_so = NULL;
	free(app->config.tex_we);
	app->config.tex_we = NULL;
	free(app->config.tex_ea);
	app->config.tex_ea = NULL;
	destroy_img(app, &app->tex_no);
	destroy_img(app, &app->tex_so);
	destroy_img(app, &app->tex_we);
	destroy_img(app, &app->tex_ea);
	destroy_img(app, &app->frame);
	if (app->mlx_ptr && app->win_ptr)
		mlx_destroy_window(app->mlx_ptr, app->win_ptr);
	app->win_ptr = NULL;
	if (app->mlx_ptr)
	{
		mlx_destroy_display(app->mlx_ptr);
		free(app->mlx_ptr);
	}
	app->mlx_ptr = NULL;
	free_split(app->map.grid);
	app->map.grid = NULL;
}
