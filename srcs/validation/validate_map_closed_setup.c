/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_closed_setup.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 07:18:00 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/05 07:18:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	finish_validation(t_bfs_context *ctx, const char *msg)
{
	cleanup_visited(ctx->visited, ctx->height);
	free(ctx->qx);
	free(ctx->qy);
	if (msg != NULL)
		error_put(msg);
	return (msg != NULL);
}

static int	init_bfs_queue(t_bfs_context *ctx)
{
	ctx->qx = NULL;
	ctx->qy = NULL;
	if ((size_t)ctx->width > SIZE_MAX / (size_t)ctx->height)
		return (finish_validation(ctx, "Error\nMap allocation failed\n"));
	ctx->qcap = (unsigned long)ctx->width * (unsigned long)ctx->height;
	if ((size_t)ctx->qcap > SIZE_MAX / sizeof(int))
		return (finish_validation(ctx, "Error\nMap allocation failed\n"));
	ctx->qx = malloc(sizeof(int) * ctx->qcap);
	ctx->qy = malloc(sizeof(int) * ctx->qcap);
	if (ctx->qx == NULL || ctx->qy == NULL)
		return (finish_validation(ctx, "Error\nMap allocation failed\n"));
	return (0);
}

int	init_bfs_context(t_bfs_context *ctx, t_app *app, char **lines, int start)
{
	if (find_player(app, lines, start) != 0)
		return (1);
	if (calculate_dimensions(lines, start, &ctx->width, &ctx->height) != 0)
		return (1);
	ctx->visited = allocate_visited(ctx->height, ctx->width);
	if (ctx->visited == NULL)
		return (error_put("Error\nMap allocation failed\n"), 1);
	if (init_bfs_queue(ctx) != 0)
		return (1);
	ctx->lines = lines;
	ctx->start = start;
	ctx->px = (int)app->player.x;
	ctx->py = (int)app->player.y;
	ctx->head = 0;
	ctx->tail = 0;
	ctx->leak = 0;
	ctx->alloc_fail = 0;
	return (0);
}
