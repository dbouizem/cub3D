/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_bfs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <dbouizem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by bbeceiro          #+#    #+#             */
/*   Updated: 2026/05/07 18:40:46 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_player(t_app *app, char **lines, int start)
{
	int	i;
	int	j;

	i = start;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (is_open_cell(lines[i][j]) && lines[i][j] != '0')
			{
				app->player.x = j + 0.5;
				app->player.y = (i - start) + 0.5;
				app->player.orientation = lines[i][j];
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	calculate_dimensions(char **lines, int start,
	int *width, int *height)
{
	int		i;
	int		j;
	size_t	map_h;
	size_t	map_w;

	*width = 0;
	*height = 0;
	i = start;
	while (lines[i])
	{
		j = ft_strlen(lines[i]);
		if (j > *width)
			*width = j;
		if (*height == INT_MAX)
			return (error_put("Error\nMap dimensions are invalid\n"), 1);
		(*height)++;
		i++;
	}
	if (*width <= 0 || *height <= 0)
		return (error_put("Error\nMap dimensions are invalid\n"), 1);
	map_h = (size_t)(*height);
	map_w = (size_t)(*width);
	if (map_h > SIZE_MAX / map_w)
		return (error_put("Error\nMap dimensions are invalid\n"), 1);
	return (0);
}

char	**allocate_visited(int height, int width)
{
	char	**visited;
	int		i;

	if (height <= 0 || width <= 0)
		return (NULL);
	if ((size_t)height > SIZE_MAX / sizeof(char *))
		return (NULL);
	visited = malloc(sizeof(char *) * height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < height)
	{
		visited[i] = ft_calloc((size_t)width, sizeof(char));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

int	scan_unreachable(char **lines, int start,
	int height, char **visited)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (lines[start + i][j])
		{
			if (is_open_cell(lines[start + i][j]) && visited[i][j] != '1')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	cleanup_visited(char **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(visited[i++]);
	free(visited);
}
