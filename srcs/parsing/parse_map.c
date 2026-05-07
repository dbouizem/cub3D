/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <dbouizem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 05:20:00 by bbeceiro          #+#    #+#             */
/*   Updated: 2026/05/07 18:39:15 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**dup_map_lines(char **lines, int start_idx, int map_h)
{
	char	**map_grid;
	int		i;

	map_grid = malloc(sizeof(char *) * ((size_t)map_h + 1));
	if (map_grid == NULL)
		return (NULL);
	i = 0;
	while (i < map_h)
	{
		map_grid[i] = ft_strdup(lines[start_idx + i]);
		if (map_grid[i] == NULL)
			return (map_grid[i] = NULL, free_split(map_grid), NULL);
		i++;
	}
	map_grid[i] = NULL;
	return (map_grid);
}

int	parse_map(t_app *app, char **lines, int start_idx, int line_count)
{
	int		map_h;
	char	**map_grid;

	if (lines == NULL || line_count <= 0 || start_idx < 0
		|| start_idx >= line_count)
		return (error_put("Error\nEmpty or invalid map input\n"), 1);
	map_h = line_count - start_idx;
	map_grid = dup_map_lines(lines, start_idx, map_h);
	if (map_grid == NULL)
		return (error_put("Error\nMap allocation failed\n"), 1);
	free_split(lines);
	app->map.grid = map_grid;
	app->map.height = map_h;
	return (0);
}
