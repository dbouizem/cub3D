/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:58:54 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/29 23:27:23 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_and_split(const char *path, char ***lines, int *line_count)
{
	char	*text;

	text = read_all_text(path);
	if (text == NULL)
		return (error_put("Error\nCannot read map file\n"), 1);
	*line_count = count_lines(text);
	if (*line_count < 0)
		return (free(text), error_put("Error\nMap file is too large\n"), 1);
	*lines = split_lines(text, *line_count);
	free(text);
	if (*lines == NULL)
		return (error_put("Error\nMap allocation failed\n"), 1);
	return (0);
}

static int	fail_parse(char **lines, const char *msg)
{
	free_split(lines);
	if (msg)
		error_put(msg);
	return (1);
}

static int	parse_loaded_file(t_app *app, const char *path, char **lines,
		int line_count)
{
	int				map_start;
	t_parse_headers	ctx;

	map_start = 0;
	ctx.lines = lines;
	ctx.line_count = line_count;
	ctx.map_start = &map_start;
	ctx.map_path = path;
	if (parse_headers(app, &ctx) != 0)
		return (fail_parse(lines, NULL));
	if (map_start >= line_count)
		return (fail_parse(lines, "Error\nMissing map block\n"));
	if (check_required_headers(app) != 0)
		return (fail_parse(lines, NULL));
	if (validate_map(app, lines, map_start) != 0)
		return (fail_parse(lines, NULL));
	if (parse_map(app, lines, map_start, line_count) != 0)
		return (fail_parse(lines, NULL));
	return (0);
}

int	parse_file(t_app *app, const char *path)
{
	char	**lines;
	int		line_count;

	if (has_cub_extension(path) == 0)
		return (error_put("Error\nInvalid file extension, expected .cub\n"), 1);
	if (read_and_split(path, &lines, &line_count) != 0)
		return (1);
	return (parse_loaded_file(app, path, lines, line_count));
}
