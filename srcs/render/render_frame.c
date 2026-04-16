/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:55:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/16 23:36:45 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				put_pixel(&app->frame, x, y, apply_flat_shading(
						app->ceiling_color, y, app->frame.height));
			else
				put_pixel(&app->frame, x, y, apply_flat_shading(
						app->floor_color, y, app->frame.height));
			x++;
		}
		y++;
	}
}

static double	get_time_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

static void	update_frame_timing(t_app *app)
{
	double	now;

	now = get_time_seconds();
	if (app->last_frame_time <= 0.0)
		app->delta_time = FRAME_DT_DEFAULT;
	else
	{
		app->delta_time = now - app->last_frame_time;
		if (app->delta_time < 0.0)
			app->delta_time = FRAME_DT_DEFAULT;
		else if (app->delta_time > FRAME_DT_MAX)
			app->delta_time = FRAME_DT_MAX;
	}
	app->last_frame_time = now;
	app->frame_count++;
}

int	draw_frame(t_app *app)
{
	t_img	saved_frame;
	int		retro_active;

	update_frame_timing(app);
	update_player_input(app);
	bonus_doors_update(app);
	bonus_hud_update(app);
	bonus_pickups_update(app);
	retro_active = retro_begin(app, &saved_frame);
	draw_background(app);
	raycast_scene(app);
	bonus_draw_sprites(app);
	bonus_draw_minimap(app);
	apply_world_vignette(app);
	if (retro_active)
		retro_render(app, &saved_frame);
	bonus_draw_hud(app);
	if (retro_active)
		mlx_put_image_to_window(app->mlx_ptr, app->win_ptr,
			app->bonus.retro.out.img_ptr, 0, 0);
	else
		mlx_put_image_to_window(app->mlx_ptr, app->win_ptr,
			app->frame.img_ptr, 0, 0);
	return (0);
}
