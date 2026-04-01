/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 20:22:12 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/01 21:13:20 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** @brief: Counts player position (N, S, E, W) in the map.
** @param lines: Map lines starting from 'start' index
** @param start: Index where map begins
** @return: Number of players found
*/
static int	count_player(char **lines, int start)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = start;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == 'N' || lines[i][j] == 'S' || lines[i][j] == 'E'
			|| lines[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

/*
** @brief: Validates that exactly one player exists
** @param app: App struct (for error message)
** @return: 0 on success, 1 on error
*/
int	validate_player(t_app *app, char **lines, int start)
{
	int	count;

	(void)app;
	count = count_player(lines, start);

	if (count == 0)
	{
		error_put("Error\n");
		write(2, "Missing player position (N/S/E/W)\n", 34);
		return (1);
	}
	if (count > 1)
	{
		error_put("Error\n");
		write(2, "Multiple player positions found\n", 32);
		return (1);
	}
	return (0);
}
