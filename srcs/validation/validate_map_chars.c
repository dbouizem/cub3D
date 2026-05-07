/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeceiro <bbeceiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:33:53 by bbeceiro          #+#    #+#             */
/*   Updated: 2026/05/07 14:33:56 by bbeceiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c)
{
	return (ft_strchr("01NSEW ", c) != NULL);
}

static int	check_all_chars(char **lines, int start)
{
	int	i;
	int	j;

	i = start;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (!is_valid_char(lines[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_chars(t_app *app, char **lines, int start)
{
	(void)app;
	if (check_all_chars(lines, start) != 0)
	{
		error_put("Error\n");
		write(2, "Map contains invalid characters\n", 32);
		return (1);
	}
	return (0);
}
