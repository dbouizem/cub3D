/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:51:41 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/02 12:10:16 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** @brief: Checks if a character is valid for the map.
** @param c: Character to check
** @return: 1 if valid ('0', '1', 'N', 'S', 'E', 'W', ' '), 0 otherwise
*/
static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

/*
** @brief: Scans all map lines and checks every character.
** @param lines: Array of map lines (starting from 'start')
** @param start: Index where map begins
** @return: 0 if all chars are valid, 1 if invalid char found
*/
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

/*
** @brief: Validates that the map contains only allowed characters.
** @param app: App struct (unused, kept for consistency)
** @param lines: Array of map lines
** @param start: Index where map begins
** @return: 0 on success, 1 on error
*/
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
