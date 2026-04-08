/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:58:54 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/08 09:55:52 by brrr1            ###   ########.fr       */
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

static int	fail_parse(char **lines, const char *msg)
{
	free_split(lines);
	if (msg)
		error_put(msg);
	return (1);
}

static int	calculate_map_dimensions(t_app *app, char **lines)
{
	int	i;
	int	max_w;
	int	h;
	int	len;

	max_w = 0;
	h = 0;
	i = app->map_start;
	while (lines[i] && is_map_like_line(lines[i]))
	{
		len = ft_strlen(lines[i]);
		if (len > max_w)
			max_w = len;
		h++;
		i++;
	}
	app->map_width = max_w;
	app->map_height = h;
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
		return (fail_parse(lines, NULL));
	if (map_start >= line_count)
		return (fail_parse(lines, "Error\nMissing map block\n"));
	if (check_required_headers(app) != 0)
		return (fail_parse(lines, NULL));
	if (validate_map(app, lines, map_start) != 0)
		return (fail_parse(lines, NULL));
	app->map_start = map_start;
	calculate_map_dimensions(app, lines);
	app->file_lines = lines;
	app->line_count = line_count;
	return (0);
}
