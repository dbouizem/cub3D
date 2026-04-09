/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_api.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:20:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 20:20:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	levels_fill_paths(t_bonus_levels *levels)
{
	levels->paths[0] = "maps/bonus/level1.cub";
	levels->paths[1] = "maps/bonus/level2.cub";
	levels->paths[2] = "maps/bonus/level3.cub";
	levels->paths[3] = "maps/bonus/level4.cub";
	levels->paths[4] = "maps/bonus/level5.cub";
	levels->paths[5] = "maps/bonus/level6.cub";
	levels->paths[6] = "maps/bonus/level7.cub";
	levels->paths[7] = "maps/bonus/level8.cub";
	levels->count = BONUS_LEVEL_MAX;
}

static int	levels_find_index(t_bonus_levels *levels, const char *path)
{
	int	i;

	i = 0;
	while (i < levels->count)
	{
		if (ft_strcmp(levels->paths[i], path) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	bonus_levels_init(t_app *app, const char *start_path)
{
	t_bonus_levels	*levels;
	int				idx;

	if (!app || !start_path)
		return (1);
	levels = &app->bonus.levels;
	ft_bzero(levels, sizeof(*levels));
	levels_fill_paths(levels);
	levels->start_path = start_path;
	idx = levels_find_index(levels, start_path);
	if (idx >= 0)
	{
		levels->current = idx;
		levels->active = 1;
	}
	return (0);
}

const char	*bonus_level_current_path(t_app *app)
{
	if (!app)
		return (NULL);
	if (app->bonus.levels.active)
		return (app->bonus.levels.paths[app->bonus.levels.current]);
	return (app->bonus.levels.start_path);
}
