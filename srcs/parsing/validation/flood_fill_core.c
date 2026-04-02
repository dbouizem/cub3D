/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_core.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 12:36:25 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/02 16:43:39 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** @brief: Finds the player's positiion and orientation in the map.
** @param app: App strauct to store results
** @param lines: Map lines
** @return: 0 on success, 1 if player not found
*/
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
			if (lines[i][j] == 'N' || lines[i][j] == 'S'
				|| lines[i][j] == 'E' || lines[i][j] == 'W')
			{
				app->player_x = j;
				app->player_y = i - start;
				app->player_dir = lines[i][j];
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

/*
** @brief: Calculates map width and height
**
*/
int	calculate_dimensions(char **lines, int start, int *width, int *height)
{
	int	i;
	int	j;

	*width = 0;
	*height = 0;
	i = start;
	while (lines[i])
	{
		j = ft_strlen(lines[i]);
		if (j > *width)
			*width = j;
		(*height)++;
		i++;
	}
	return (0);
}

/*
** @brief: Allocates and initializes the visited grid.
*/
char	**allocate_visited(int height, int width)
{
	char	**visited;
	int		i;

	visited = malloc(sizeof(char *) * height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < height)
	{
		visited[i] = malloc(sizeof(char) * width);
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		ft_bzero(visited[i], width);
		i++;
	}
	return (visited);
}

/*
** @brief: Scans for unvisited walkable cells.
*/
int	scan_unreachable(char **lines, int start, int height, char **visited)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (lines[start + i][j])
		{
			if (lines[start + i][j] == '0' && visited[i][j] != '1')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/*
** @brief: Frees the visited grid.
*/
void	cleanup_visited(char **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(visited[i++]);
	free(visited);
}
