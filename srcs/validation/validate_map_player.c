/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeceiro <bbeceiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:34:23 by bbeceiro          #+#    #+#             */
/*   Updated: 2026/05/07 14:34:27 by bbeceiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			if (ft_strchr("NSEW", lines[i][j]))
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

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
