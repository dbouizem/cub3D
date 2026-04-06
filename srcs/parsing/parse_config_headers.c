/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_headers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/05 05:20:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_header_entry(t_app *app, char *line, const char *map_path)
{
	if (starts_with_id(line, "NO"))
		return (parse_texture(&app->config.tex_no, line, map_path));
	if (starts_with_id(line, "SO"))
		return (parse_texture(&app->config.tex_so, line, map_path));
	if (starts_with_id(line, "WE"))
		return (parse_texture(&app->config.tex_we, line, map_path));
	if (starts_with_id(line, "EA"))
		return (parse_texture(&app->config.tex_ea, line, map_path));
	if (starts_with_one_id(line, 'F'))
		return (parse_color(app->config.floor_rgb, line));
	if (starts_with_one_id(line, 'C'))
		return (parse_color(app->config.ceiling_rgb, line));
	return (PARSE_NOT_HEADER);
}

int	starts_with_header_prefix(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (0);
	return (ft_strchr("NSWEFC", line[i]) != NULL);
}

int	has_required_headers_loaded(t_app *app)
{
	if (!app->config.tex_no || !app->config.tex_so
		|| !app->config.tex_we || !app->config.tex_ea)
		return (0);
	if (app->config.floor_rgb[0] < 0 || app->config.ceiling_rgb[0] < 0)
		return (0);
	return (1);
}
