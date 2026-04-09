/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:00:15 by dbouizem          #+#    #+#             */
/*   Updated: 2026/03/31 17:00:16 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bind_window_hooks(t_app *app)
{
	mlx_hook(app->win_ptr, EVENT_KEYPRESS, 1L << 0, handle_keypress, app);
	mlx_hook(app->win_ptr, EVENT_KEYRELEASE, 1L << 1, handle_keyrelease, app);
	mlx_hook(app->win_ptr, EVENT_MOUSEMOVE, 1L << 6, handle_mouse_move, app);
	mlx_hook(app->win_ptr, EVENT_DESTROY, 0, close_window, app);
}

static int	start_game_loop(t_app *app)
{
	bind_window_hooks(app);
	mlx_loop_hook(app->mlx_ptr, draw_frame, app);
	mlx_loop(app->mlx_ptr);
	return (0);
}

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
		return (error_put("Error\nUsage: ./cub3D <map.cub>\n"), 1);
	init_app(&app);
	if (parse_file(&app, argv[1]) != 0)
		return (free_app(&app), 1);
	init_player_vectors(&app);
	if (init_mlx(&app) != 0)
		return (free_app(&app), 1);
	if (start_game_loop(&app) != 0)
		return (free_app(&app), 1);
	free_app(&app);
	return (0);
}
