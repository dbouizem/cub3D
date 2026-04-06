/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/03 00:00:00 by brrr1            ###   ########.fr       */
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
		return (error_put("Error\nMissing player position (N/S/E/W)\n"), 1);
	if (count > 1)
		return (error_put("Error\nMultiple player positions found\n"), 1);
	return (0);
}
