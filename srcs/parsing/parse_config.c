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
	if (status == PARSE_NOT_HEADER && has_required_headers_loaded(app) == 0
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
	if (has_required_headers_loaded(app))
		return (0);
	if (app->config.tex_no == NULL || app->config.tex_so == NULL
		|| app->config.tex_we == NULL || app->config.tex_ea == NULL)
		return (error_put("Error\nMissing texture identifiers\n"), 1);
	if (app->config.floor_rgb[0] < 0 || app->config.ceiling_rgb[0] < 0)
		return (error_put("Error\nMissing floor/ceiling colors\n"), 1);
	return (0);
}
