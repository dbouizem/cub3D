/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_boundaries.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 08:44:04 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/03 13:07:11 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** @brief: Checks if the top row of the map is enclosed by walls.
** @param lines: Map lines array
** @param start: Index where map begins
** @return: 0 if enclosed, 1 if not enclosed
*/
static int	check_top_row(char **lines, int start)
{
	int	i;

	i = 0;
	while (lines[start][i])
	{
		if (lines[start][i] != '1')
		{
			error_put("Error\n");
			write(2, "Map is not enclosed by walls (top)\n", 35);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** @brief: Checks if the bottom row of the map is enclosed by walls.
** @param lines: Map lines array
** @param start: Index where map begins
** @return: 0 if enclosed, 1 if not enclosed
*/
static int	check_bottom_row(char **lines, int start)
{
	int	last_row;
	int	i;

	last_row = start;
	while (lines[last_row])
		last_row++;
	last_row--;
	i = 0;
	while (lines[last_row][i])
	{
		if (lines[last_row][i] != '1')
		{
			error_put("Error\n");
			write(2, "Map is not ecnlosed by walls (bottom)\n", 38);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** @brief: Checks if the left column of the map is enclosed by walls.
** @param lines: Map lines array
** @param start: Index where map begins
** @return: 0 if enclosed, 1 if not enclosed
*/
static int	check_left_col(char **lines, int start)
{
	int	i;

	i = start;
	while (lines[i])
	{
		if (lines[i][0] != '1')
		{
			error_put("Error\n");
			write(2, "Map is not ecnlosed by walls (left)\n", 36);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** @brief: Checks if the right column of the map is enclosed by walls.
** @param lines: Map lines array
** @param start: Index where map begins
** @return: 0 if enclosed, 1 if not enclosed
*/
static int	check_right_col(char **lines, int start)
{
	int	i;
	int	len;

	i = start;
	while (lines[i])
	{
		len = ft_strlen(lines[i]);
		if (len > 0 && lines[i][len - 1] != '1')
		{
			error_put("Error\n");
			write(2, "Map is not enclosed by walls (right)\n", 37);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
** @brief: Validates that the map is enclosed by walls on all four sides.
** @param app: App struct (unused, kept for consistency)
** @param lines: Map lines array
** @param start: Index where map begins
** @return: 0 on success, 1 if any boundary is not enclosed
*/
int	validate_boundaries(t_app *app, char **lines, int start)
{
	(void)app;
	if (check_top_row(lines, start) != 0)
		return (1);
	if (check_bottom_row(lines, start) != 0)
		return (1);
	if (check_left_col(lines, start) != 0)
		return (1);
	if (check_right_col(lines, start) != 0)
		return (1);
	return (0);
}
