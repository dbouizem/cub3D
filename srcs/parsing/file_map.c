/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 10:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/03 10:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_char(char c)
{
	return (ft_strchr(" 01NSEW", c) != NULL);
}

static char	map_char_at(char **lines, int row, int col, int lim[2])
{
	size_t	len;

	if (row < lim[0] || row >= lim[1] || col < 0)
		return (' ');
	len = ft_strlen(lines[row]);
	if ((size_t)col >= len)
		return (' ');
	return (lines[row][col]);
}

static int	is_closed_around(char **lines, int row, int col, int lim[2])
{
	if (!ft_strchr("01NSEW", map_char_at(lines, row - 1, col, lim)))
		return (0);
	if (!ft_strchr("01NSEW", map_char_at(lines, row + 1, col, lim)))
		return (0);
	if (!ft_strchr("01NSEW", map_char_at(lines, row, col - 1, lim)))
		return (0);
	if (!ft_strchr("01NSEW", map_char_at(lines, row, col + 1, lim)))
		return (0);
	return (1);
}

static int	check_map_lines(char **lines, int line_count, int lim[2])
{
	int	i;
	int	j;

	i = lim[0];
	while (i < line_count && !is_empty_line(lines[i]))
	{
		j = 0;
		while (lines[i][j])
		{
			if (!is_map_char(lines[i][j]))
				return (error_put("Error\nInvalid character in map\n"), 1);
			j++;
		}
		i++;
	}
	lim[1] = i;
	while (i < line_count)
	{
		if (!is_empty_line(lines[i]))
			return (error_put("Error\nMap must be the last block\n"), 1);
		i++;
	}
	return (0);
}

int	validate_map_block(char **lines, int line_count, int map_start)
{
	int	row;
	int	col;
	int	player_count;
	int	lim[2];

	lim[0] = map_start;
	if (check_map_lines(lines, line_count, lim) != 0)
		return (1);
	player_count = 0;
	row = map_start - 1;
	while (++row < lim[1])
	{
		col = -1;
		while (lines[row][++col])
		{
			player_count += (ft_strchr("NSEW", lines[row][col]) != NULL);
			if (ft_strchr("0NSEW", lines[row][col])
				&& is_closed_around(lines, row, col, lim) == 0)
				return (error_put("Error\nMap is not closed\n"), 1);
		}
	}
	if (player_count != 1)
		return (error_put("Error\nMap must contain exactly one player\n"), 1);
	return (0);
}
