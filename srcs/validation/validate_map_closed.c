/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_closed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:55:52 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/02 18:20:10 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	handle_validation_error(char **visited, int height,
	const char *msg, int len)
{
	cleanup_visited(visited, height);
	error_put("Error\n");
	write(2, msg, len);
	return (1);
}

/*
** @brief: Checks and enqueues a valid neighbor.
*/
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
	enqueue(&ctx->queue, nx, ny);
}

static void	run_bfs(t_bfs_context *ctx)
{
	int	dx[4];
	int	dy[4];
	int	i;
	int	x;
	int	y;

	init_directions(dx, dy);
	enqueue(&ctx->queue, ctx->px, ctx->py);
	ctx->visited[ctx->py][ctx->px] = '1';
	while (ctx->leak == 0 && dequeue(&ctx->queue, &x, &y))
	{
		i = 0;
		while (i < 4)
		{
			try_enqueue(ctx, x + dx[i], y + dy[i]);
			if (ctx->leak)
				return ;
			i++;
		}
	}
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
	ctx.px = app->player_x;
	ctx.py = app->player_y;
	ctx.leak = 0;
	run_bfs(&ctx);
	if (ctx.leak)
		return (handle_validation_error(ctx.visited, ctx.height,
				"Map is not enclosed by walls\n", 29));
	if (scan_unreachable(lines, start, ctx.height, ctx.visited))
		return (handle_validation_error(ctx.visited, ctx.height,
				"Map contains unreachable areas\n", 31));
	cleanup_visited(ctx.visited, ctx.height);
	free_queue(ctx.queue);
	return (0);
}
