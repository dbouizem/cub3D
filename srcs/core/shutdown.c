/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/16 00:00:00 by dbouizem         ###   ########.fr       */
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

static void	free_config(t_app *app)
{
	free(app->config.tex_no);
	app->config.tex_no = NULL;
	free(app->config.tex_so);
	app->config.tex_so = NULL;
	free(app->config.tex_we);
	app->config.tex_we = NULL;
	free(app->config.tex_ea);
	app->config.tex_ea = NULL;
}

/*
** Bonus cleanup hooks:
** mandatory links no-op destroy functions, bonus releases real bonus assets.
*/
static void	destroy_textures(t_app *app)
{
	destroy_img(app, &app->tex_no);
	destroy_img(app, &app->tex_so);
	destroy_img(app, &app->tex_we);
	destroy_img(app, &app->tex_ea);
	destroy_img(app, &app->bonus.retro.minimap);
	bonus_destroy_wall_textures(app);
	retro_shutdown(app);
	bonus_doors_shutdown(app);
	bonus_hud_shutdown(app);
	bonus_pickups_shutdown(app);
	bonus_sprites_shutdown(app);
	destroy_img(app, &app->frame);
}

void	free_app(t_app *app)
{
	free_config(app);
	destroy_textures(app);
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

int	close_window(t_app *app)
{
	free_app(app);
	exit(0);
	return (0);
}
