/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 09:20:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/06 10:40:04 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	retro_ready(t_app *app)
{
	if (!app || app->bonus.retro.enabled == 0)
		return (0);
	if (!app->bonus.retro.fb.addr || !app->bonus.retro.out.addr)
		return (0);
	if (app->bonus.retro.fb.width <= 0 || app->bonus.retro.fb.height <= 0)
		return (0);
	if (app->bonus.retro.out.width <= 0 || app->bonus.retro.out.height <= 0)
		return (0);
	return (1);
}

int	retro_init(t_app *app)
{
	if (!app || !app->mlx_ptr || !app->win_ptr || app->win_w <= 0
		|| app->win_h <= 0)
		return (1);
	retro_reset_img(&app->bonus.retro.fb);
	retro_reset_img(&app->bonus.retro.out);
	retro_reset_img(&app->bonus.retro.minimap);
	app->bonus.retro.enabled = 0;
	if (retro_init_img(app, &app->bonus.retro.fb,
			BONUS_RENDER_W, BONUS_RENDER_H) != 0)
		return (error_put(BONUS_WARN_FB_INIT), 0);
	if (retro_init_img(app, &app->bonus.retro.out, app->win_w,
			app->win_h) != 0)
		return (retro_destroy_img(app, &app->bonus.retro.fb),
			error_put(BONUS_WARN_OUT_INIT), 0);
	if (retro_init_img(app, &app->bonus.retro.minimap,
			(BONUS_MINIMAP_RADIUS * 2 + 1) * BONUS_MINIMAP_TILE,
			(BONUS_MINIMAP_RADIUS * 2 + 1) * BONUS_MINIMAP_TILE) != 0)
		return (retro_destroy_img(app, &app->bonus.retro.fb),
			retro_destroy_img(app, &app->bonus.retro.out),
			error_put("Warning\nBonus disabled: minimap init failed\n"), 0);
	app->bonus.retro.enabled = 1;
	return (0);
}

int	retro_begin(t_app *app, t_img *saved_frame)
{
	if (!saved_frame || !retro_ready(app))
		return (0);
	*saved_frame = app->frame;
	app->frame = app->bonus.retro.fb;
	return (1);
}

int	retro_render(t_app *app, t_img *saved_frame)
{
	if (!saved_frame || !retro_ready(app))
		return (0);
	retro_upscale_to_out(app);
	app->frame = *saved_frame;
	mlx_put_image_to_window(app->mlx_ptr, app->win_ptr,
		app->bonus.retro.out.img_ptr, 0, 0);
	return (1);
}

void	retro_shutdown(t_app *app)
{
	retro_destroy_img(app, &app->bonus.retro.fb);
	retro_destroy_img(app, &app->bonus.retro.out);
	retro_destroy_img(app, &app->bonus.retro.minimap);
	app->bonus.retro.enabled = 0;
}
