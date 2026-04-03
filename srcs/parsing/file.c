/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:58:54 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/01 20:45:14 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_and_split(const char *path, char ***lines, int *line_count)
{
	char	*text;

	text = read_all_text(path);
	if (!text)
		return (error_put("Error\nCannot read map file\n"), 1);
	*line_count = count_lines(text);
	if (*line_count < 0)
		return (free(text), error_put("Error\nMap file is too large\n"), 1);
	*lines = split_lines(text, *line_count);
	free(text);
	if (!*lines)
		return (error_put("Error\nMap allocation failed\n"), 1);
	return (0);
}

int	parse_file(t_app *app, const char *path)
{
	char	**lines;
	int		line_count;
	int		map_start;

	if (!has_cub_extension(path))
		return (error_put("Error\nInvalid file extension, expected .cub\n"), 1);
	if (read_and_split(path, &lines, &line_count) != 0)
		return (1);
	map_start = 0;
	if (parse_headers(app, lines, line_count, &map_start) != 0)
		return (free_split(lines), 1);
	if (validate_map(app, lines, map_start) != 0)
		return (free_split(lines), 1);
	if (map_start >= line_count)
		return (free_split(lines), error_put("Error\nMissing map block\n"), 1);
	if (check_required_headers(app) != 0)
		return (free_split(lines), 1);
	if (validate_map_block(lines, line_count, map_start) != 0)
		return (free_split(lines), 1);
	app->file_lines = lines;
	app->line_count = line_count;
	app->map_start = map_start;
	return (0);
}
