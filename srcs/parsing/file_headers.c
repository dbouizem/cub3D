/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_headers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:59:12 by dbouizem          #+#    #+#             */
/*   Updated: 2026/03/31 16:59:13 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	valid_texture_path(const char *path)
{
	size_t	len;
	int		fd;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (error_put("Error\nTexture must be an .xpm file\n"), 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_put("Error\nTexture path is invalid or unreadable\n"), 1);
	close(fd);
	return (0);
}

int	parse_texture(char **slot, const char *line)
{
	int		i;
	char	*value;

	if (*slot)
		return (error_put("Error\nDuplicate texture identifier\n"), 1);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	value = dup_trimmed_value(line, i + 2);
	if (!value)
		return (error_put("Error\nMissing texture path\n"), 1);
	if (valid_texture_path(value) != 0)
		return (free(value), 1);
	*slot = value;
	return (0);
}

static int	parse_until_map(t_app *app, char **lines, int line_count, int *i)
{
	int	status;

	status = PARSE_OK;
	while (*i < line_count)
	{
		if (is_empty_line(lines[*i]))
		{
			(*i)++;
			continue ;
		}
		status = parse_header_entry(app, lines[*i]);
		if (status != PARSE_OK)
			return (status);
		(*i)++;
	}
	return (PARSE_OK);
}

int	parse_headers(t_app *app, char **lines, int line_count, int *map_start)
{
	int	i;
	int	status;

	i = 0;
	status = parse_until_map(app, lines, line_count, &i);
	if (status == PARSE_ERR)
		return (1);
	if (status == PARSE_NOT_HEADER && !has_required_headers_loaded(app)
		&& starts_with_header_prefix(lines[i]))
		return (error_put("Error\nInvalid header format\n"), 1);
	if (i < line_count && !is_map_like_line(lines[i]))
	{
		if (starts_with_header_prefix(lines[i]))
			return (error_put("Error\nInvalid header format\n"), 1);
		return (error_put("Error\nUnknown identifier in config\n"), 1);
	}
	*map_start = i;
	return (0);
}

int	check_required_headers(t_app *app)
{
	if (has_required_headers_loaded(app))
		return (0);
	if (!app->config.tex_no || !app->config.tex_so
		|| !app->config.tex_we || !app->config.tex_ea)
		return (error_put("Error\nMissing texture identifiers\n"), 1);
	if (app->config.floor_rgb[0] < 0 || app->config.ceiling_rgb[0] < 0)
		return (error_put("Error\nMissing floor/ceiling colors\n"), 1);
	return (0);
}
