/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retro_noop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 09:45:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/05/06 15:54:47 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Mandatory mode does not create the bonus retro framebuffer.
*/
int	retro_init(t_app *app)
{
	(void)app;
	return (0);
}

/*
** Rendering keeps using the normal frame buffer in mandatory mode.
*/
int	retro_begin(t_app *app, t_img *saved_frame)
{
	(void)app;
	(void)saved_frame;
	return (0);
}

/*
** No retro upscale pass is applied in mandatory mode.
*/
int	retro_render(t_app *app, t_img *saved_frame)
{
	(void)app;
	(void)saved_frame;
	return (0);
}

/*
** No retro images were allocated by the mandatory build.
*/
void	retro_shutdown(t_app *app)
{
	(void)app;
}

/*
** Resolution presets are a bonus-only convenience.
*/
int	bonus_apply_resolution_preset(t_app *app, int keycode)
{
	(void)app;
	(void)keycode;
	return (0);
}
