/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_current.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 19:15:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 19:15:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char	*bonus_level_current_path(t_app *app)
{
	if (!app)
		return (NULL);
	if (app->bonus.levels.active)
		return (app->bonus.levels.paths[app->bonus.levels.current]);
	return (app->bonus.levels.start_path);
}
