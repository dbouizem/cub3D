/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_closed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:55:52 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/05 06:45:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	map_cell(t_bfs_context *ctx, int x, int y)
{
	size_t	row_len;

	if (x < 0 || y < 0)
		return (' ');
	row_len = ft_strlen(ctx->lines[ctx->start + y]);
	if ((size_t)x >= row_len)
		return (' ');
	return (ctx->lines[ctx->start + y][x]);
}

static int	push_node(t_bfs_context *ctx, int x, int y)
{
	if (ctx->tail >= ctx->qcap)
		return (ctx->alloc_fail = 1, 1);
	ctx->qx[ctx->tail] = x;
	ctx->qy[ctx->tail] = y;
	ctx->tail++;
	return (0);
}

static int	visit_neighbor(t_bfs_context *ctx, int nx, int ny)
{
	char	cell;

	if (nx < 0 || ny < 0 || nx >= ctx->width || ny >= ctx->height)
		return (ctx->leak = 1, 0);
	cell = map_cell(ctx, nx, ny);
	if (cell == ' ')
		return (ctx->leak = 1, 0);
	if (bonus_is_solid_tile(cell) || ctx->visited[ny][nx] == '1')
		return (0);
	ctx->visited[ny][nx] = '1';
	return (push_node(ctx, nx, ny));
}

static int	run_bfs(t_bfs_context *ctx)
{
	int	dx[4];
	int	dy[4];
	int	x;
	int	y;
	int	i;

	init_directions(dx, dy);
	ctx->visited[ctx->py][ctx->px] = '1';
	if (push_node(ctx, ctx->px, ctx->py) != 0)
		return (1);
	while (ctx->head < ctx->tail && ctx->leak == 0 && ctx->alloc_fail == 0)
	{
		x = ctx->qx[ctx->head];
		y = ctx->qy[ctx->head];
		ctx->head++;
		i = 0;
		while (i < 4)
		{
			if (visit_neighbor(ctx, x + dx[i], y + dy[i]) != 0)
				return (1);
			i++;
		}
	}
	return (0);
}

int	check_enclosure(t_app *app, char **lines, int start)
{
	t_bfs_context	ctx;

	if (init_bfs_context(&ctx, app, lines, start) != 0)
		return (1);
	if (run_bfs(&ctx) != 0 || ctx.alloc_fail != 0)
		return (finish_validation(&ctx, "Error\nMap allocation failed\n"));
	if (ctx.leak != 0)
		return (finish_validation(&ctx,
				"Error\nMap is not enclosed by walls\n"));
	if (scan_unreachable(lines, start, ctx.height, ctx.visited) != 0)
		return (finish_validation(&ctx,
				"Error\nMap contains unreachable areas\n"));
	return (finish_validation(&ctx, NULL));
}
