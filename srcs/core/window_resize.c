/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 13:45:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 13:45:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_img_local(t_app *app, t_img *img)
{
	if (app->mlx_ptr && img->img_ptr)
		mlx_destroy_image(app->mlx_ptr, img->img_ptr);
	img->img_ptr = NULL;
	img->addr = NULL;
}

static int	create_frame_buffer(t_app *app)
{
	app->frame.img_ptr = mlx_new_image(app->mlx_ptr, app->win_w, app->win_h);
	if (!app->frame.img_ptr)
		return (1);
	app->frame.width = app->win_w;
	app->frame.height = app->win_h;
	app->frame.addr = mlx_get_data_addr(app->frame.img_ptr, &app->frame.bpp,
			&app->frame.line_len, &app->frame.endian);
	if (!app->frame.addr)
		return (destroy_img_local(app, &app->frame), 1);
	return (0);
}

/*
** Bonus hooks:
** mandatory only recreates the main frame; bonus also recreates retro/sprite data.
*/
static int	recreate_render_targets(t_app *app)
{
	destroy_img_local(app, &app->frame);
	if (create_frame_buffer(app) != 0)
		return (1);
	retro_shutdown(app);
	if (retro_init(app) != 0)
		return (1);
	if (bonus_sprites_resize_zbuf(app, app->win_w) != 0)
		return (1);
	app->input.mouse_ready = 0;
	app->input.mouse_dx = 0;
	return (0);
}

static int	close_window_error(t_app *app)
{
	free_app(app);
	exit(1);
	return (1);
}

int	resize_window(t_app *app, int w, int h, int recreate_window)
{
	if (!app || !app->mlx_ptr || !app->win_ptr || w <= 0 || h <= 0)
		return (0);
	if (w == app->win_w && h == app->win_h)
		return (0);
	app->win_w = w;
	app->win_h = h;
	if (recreate_window)
	{
		mlx_destroy_window(app->mlx_ptr, app->win_ptr);
		app->win_ptr = mlx_new_window(app->mlx_ptr, w, h, "cub3D");
		if (!app->win_ptr)
			return (close_window_error(app));
		mlx_hook(app->win_ptr, EVENT_KEYPRESS, 1L << 0, handle_keypress, app);
		mlx_hook(app->win_ptr, EVENT_KEYRELEASE, 1L << 1, handle_keyrelease,
			app);
		mlx_hook(app->win_ptr, EVENT_BUTTONPRESS, 1L << 2, handle_mouse_press,
			app);
		mlx_hook(app->win_ptr, EVENT_MOUSEMOVE, 1L << 6, handle_mouse_move,
			app);
		mlx_hook(app->win_ptr, EVENT_DESTROY, 0, close_window, app);
	}
	if (recreate_render_targets(app) != 0)
		return (close_window_error(app));
	return (1);
}
