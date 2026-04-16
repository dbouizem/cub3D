/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:59:12 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/05 05:20:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_header_entry(t_app *app, char *line, const char *map_path)
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

static int	starts_with_header_prefix(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (0);
	return (ft_strchr("NSWEFC", line[i]) != NULL);
}

static int	parse_until_map(t_app *app, t_parse_headers *ctx, int *i)
{
	int	status;

	status = PARSE_OK;
	while (*i < ctx->line_count)
	{
		if (is_empty_line(ctx->lines[*i]))
		{
			(*i)++;
			continue ;
		}
		status = parse_header_entry(app, ctx->lines[*i], ctx->map_path);
		if (status == PARSE_OK)
			(*i)++;
		else
			return (status);
	}
	return (PARSE_OK);
}

int	parse_headers(t_app *app, t_parse_headers *ctx)
{
	int	i;
	int	status;

	i = 0;
	status = parse_until_map(app, ctx, &i);
	if (status == PARSE_ERR)
		return (1);
	if (status == PARSE_NOT_HEADER
		&& (!app->config.tex_no || !app->config.tex_so
			|| !app->config.tex_we || !app->config.tex_ea
			|| app->config.floor_rgb[0] < 0
			|| app->config.ceiling_rgb[0] < 0)
		&& starts_with_header_prefix(ctx->lines[i]))
		return (error_put("Error\nInvalid header format\n"), 1);
	if (i < ctx->line_count && is_map_like_line(ctx->lines[i]) == 0)
	{
		if (starts_with_header_prefix(ctx->lines[i]))
			return (error_put("Error\nInvalid header format\n"), 1);
		return (error_put("Error\nUnknown identifier in config\n"), 1);
	}
	*ctx->map_start = i;
	return (0);
}

int	check_required_headers(t_app *app)
{
	if (app->config.tex_no && app->config.tex_so
		&& app->config.tex_we && app->config.tex_ea
		&& app->config.floor_rgb[0] >= 0
		&& app->config.ceiling_rgb[0] >= 0)
		return (0);
	if (app->config.tex_no == NULL || app->config.tex_so == NULL
		|| app->config.tex_we == NULL || app->config.tex_ea == NULL)
		return (error_put("Error\nMissing texture identifiers\n"), 1);
	if (app->config.floor_rgb[0] < 0 || app->config.ceiling_rgb[0] < 0)
		return (error_put("Error\nMissing floor/ceiling colors\n"), 1);
	return (0);
}
