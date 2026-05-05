/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api_noop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 09:45:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/06 12:43:11 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** noop = no operation
** Mandatory fallback implementation:
** - linked by default `make` build
** - keeps retro API calls no-op in mandatory mode
** - replaced by real retro implementation in `make bonus`
*/

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
** Mandatory floor and ceiling keep their original RGB color.
*/
int	apply_flat_shading(int color, int y, int height)
{
	(void)y;
	(void)height;
	return (color);
}
