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

int	retro_init(t_app *app)
{
	(void)app;
	return (0);
}

int	retro_begin(t_app *app, t_img *saved_frame)
{
	(void)app;
	(void)saved_frame;
	return (0);
}

int	retro_render(t_app *app, t_img *saved_frame)
{
	(void)app;
	(void)saved_frame;
	return (0);
}

void	retro_shutdown(t_app *app)
{
	(void)app;
}
