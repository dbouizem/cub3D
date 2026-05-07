/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_closed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeceiro <bbeceiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:34:17 by bbeceiro          #+#    #+#             */
/*   Updated: 2026/05/07 14:34:19 by bbeceiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_validation_error(t_bfs_context *ctx, const char *msg,
		int len)
{
	cleanup_visited(ctx->visited, ctx->height);
	free_queue(ctx->queue);
	error_put("Error\n");
	write(2, msg, len);
	return (1);
}

static void	try_enqueue(t_bfs_context *ctx, int nx, int ny)
{
	size_t	len;
	char	cell;

	if (ctx->leak)
		return ;
	if (nx < 0 || ny < 0 || nx >= ctx->width || ny >= ctx->height)
		return (ctx->leak = 1, (void)0);
	len = ft_strlen(ctx->lines[ctx->start + ny]);
	if ((size_t)nx >= len)
		return (ctx->leak = 1, (void)0);
	cell = ctx->lines[ctx->start + ny][nx];
	if (cell == ' ')
		return (ctx->leak = 1, (void)0);
	if (cell == '1')
		return ;
	if (ctx->visited[ny][nx] == '1')
		return ;
	ctx->visited[ny][nx] = '1';
	if (enqueue(&ctx->queue, &ctx->queue_tail, nx, ny) != 0)
	{
		ctx->visited[ny][nx] = 0;
		ctx->alloc_error = 1;
	}
}

static void	run_bfs(t_bfs_context *ctx)
{
	int	dx[4];
	int	dy[4];
	int	x;
	int	y;

	init_directions(dx, dy);
	if (enqueue(&ctx->queue, &ctx->queue_tail, ctx->px, ctx->py) != 0)
	{
		ctx->alloc_error = 1;
		return ;
	}
	ctx->visited[ctx->py][ctx->px] = '1';
	while (ctx->leak == 0 && ctx->alloc_error == 0)
	{
		if (dequeue(&ctx->queue, &x, &y) == 0)
			break ;
		if (ctx->queue == NULL)
			ctx->queue_tail = NULL;
		try_enqueue(ctx, x + dx[0], y + dy[0]);
		try_enqueue(ctx, x + dx[1], y + dy[1]);
		try_enqueue(ctx, x + dx[2], y + dy[2]);
		try_enqueue(ctx, x + dx[3], y + dy[3]);
	}
}

static int	finalize_bfs_validation(t_bfs_context *ctx)
{
	if (ctx->alloc_error)
		return (handle_validation_error(ctx,
				"Memory allocation failed during map validation\n", 45));
	if (ctx->leak)
		return (handle_validation_error(ctx,
				"Map is not enclosed by walls\n", 29));
	if (scan_unreachable(ctx->lines, ctx->start, ctx->height, ctx->visited))
		return (handle_validation_error(ctx,
				"Map contains unreachable areas\n", 31));
	cleanup_visited(ctx->visited, ctx->height);
	free_queue(ctx->queue);
	return (0);
}

int	check_enclosure(t_app *app, char **lines, int start)
{
	t_bfs_context	ctx;

	if (find_player(app, lines, start) != 0)
		return (1);
	calculate_dimensions(lines, start, &ctx.width, &ctx.height);
	ctx.visited = allocate_visited(ctx.height, ctx.width);
	if (!ctx.visited)
		return (1);
	ctx.lines = lines;
	ctx.start = start;
	ctx.queue = NULL;
	ctx.queue_tail = NULL;
	ctx.px = app->player_x;
	ctx.py = app->player_y;
	ctx.leak = 0;
	ctx.alloc_error = 0;
	run_bfs(&ctx);
	return (finalize_bfs_validation(&ctx));
}
