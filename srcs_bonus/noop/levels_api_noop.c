/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_api_noop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:20:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 20:20:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Mandatory mode uses only the .cub path passed by the user.
*/
int	bonus_levels_init(t_app *app, const char *start_path)
{
	(void)app;
	(void)start_path;
	return (0);
}

/*
** Returning NULL tells main() to keep argv[1] as the map path.
*/
const char	*bonus_level_current_path(t_app *app)
{
	(void)app;
	return (NULL);
}

/*
** Level switching is disabled in mandatory mode.
*/
int	bonus_load_next_level(t_app *app)
{
	(void)app;
	return (1);
}
