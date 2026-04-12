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

static const char	*skip_relative_prefix(const char *path)
{
	while (path && path[0] == '.' && path[1] == '/')
		path += 2;
	return (path);
}

static int	path_matches_level(const char *level_path, const char *input_path)
{
	size_t		level_len;
	size_t		input_len;
	const char	*normalized;
	const char	*suffix;

	if (!level_path || !input_path)
		return (0);
	normalized = skip_relative_prefix(input_path);
	if (ft_strcmp(level_path, normalized) == 0)
		return (1);
	level_len = ft_strlen(level_path);
	input_len = ft_strlen(normalized);
	if (input_len < level_len)
		return (0);
	suffix = normalized + input_len - level_len;
	if (ft_strcmp(level_path, suffix) != 0)
		return (0);
	if (suffix == normalized)
		return (1);
	if (*(suffix - 1) == '/')
		return (1);
	return (0);
}

static int	levels_find_index(t_bonus_levels *levels, const char *path)
{
	int	i;

	i = 0;
	while (i < levels->count)
	{
		if (path_matches_level(levels->paths[i], path))
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
