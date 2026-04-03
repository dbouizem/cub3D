/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_bfs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:55:52 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/03 13:03:52 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** @brief: Handles the error case for unreachable areas.
** @param visited: Visited grid to clean up
** @param height: Number of rows in the grid
** @return: 1 (error code)
*/
static int	handle_unreachable_error(char **visited, int height)
{
	cleanup_visited(visited, height);
	error_put("Error\n");
	write(2, "Map contains unreachable areas\n", 31);
	return (1);
}

/*
** @brief: Checks and enqueues a valid neighbor if it is walkable and unvisited.
** @param ctx: BFS context containing map and visited data
** @param nx: Neighbor x coordinate
** @param ny: Neighbor y coordinate
*/
static void	try_enqueue(t_bfs_context *ctx, int nx, int ny)
{
	if (nx < 0 || nx >= ctx->width || ny < 0 || ny >= ctx->height)
		return ;
	if (ctx->lines[ctx->start + ny][nx] == '1')
		return ;
	if (ctx->visited[ny][nx] == '1')
		return ;
	ctx->visited[ny][nx] = '1';
	enqueue(&ctx->queue, nx, ny);
}

/*
** @brief: Processes one cell in the BFS queue by checking its four neighbors.
** @param ctx: BFS context containing map and visited data
** @param x: Current cell x coordinate
** @param y: Current cell y coordinate
*/
static void	process_cell(t_bfs_context *ctx, int x, int y)
{
	int	dx[4];
	int	dy[4];
	int	i;
	int	nx;
	int	ny;

	init_directions(dx, dy);
	i = 0;
	while (i < 4)
	{
		nx = x + dx[i];
		ny = y + dy[i];
		try_enqueue(ctx, nx, ny);
		i++;
	}
}

/*
** @brief: Performs BFS flood-fill from player position until queue is empty.
** @param ctx: BFS context containing queue, visited, and map info
*/
static void	run_bfs(t_bfs_context *ctx)
{
	int	x;
	int	y;

	enqueue(&ctx->queue, ctx->px, ctx->py);
	ctx->visited[ctx->py][ctx->px] = '1';
	while (dequeue(&ctx->queue, &x, &y))
		process_cell(ctx, x, y);
}

/*
** @brief: Validates that all walkable cells are reachable from the player.
** @param app: App struct containing player position
** @param lines: Map lines array
** @param start: Index where map begins in lines array
** @return: 0 if map is enclosed, 1 if unreachable areas exist or error
*/
int	check_enclosure(t_app *app, char **lines, int start)
{
	int				width;
	int				height;
	char			**visited;
	t_bfs_context	ctx;

	if (find_player(app, lines, start) != 0)
		return (1);
	calculate_dimensions(lines, start, &width, &height);
	visited = allocate_visited(height, width);
	if (!visited)
		return (1);
	ctx.lines = lines;
	ctx.start = start;
	ctx.width = width;
	ctx.height = height;
	ctx.visited = visited;
	ctx.queue = NULL;
	ctx.px = app->player_x;
	ctx.py = app->player_y;
	run_bfs(&ctx);
	if (scan_unreachable(lines, start, height, visited))
		return (handle_unreachable_error(visited, height));
	cleanup_visited(visited, height);
	return (0);
}
