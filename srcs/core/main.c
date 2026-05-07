/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:00:15 by dbouizem          #+#    #+#             */
/*   Updated: 2026/05/05 22:14:49 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	bind_window_hooks(t_app *app)
{
	mlx_hook(app->win_ptr, EVENT_KEYPRESS, 1L << 0, handle_keypress, app);
	mlx_hook(app->win_ptr, EVENT_KEYRELEASE, 1L << 1, handle_keyrelease, app);
	mlx_hook(app->win_ptr, EVENT_BUTTONPRESS, 1L << 2, handle_mouse_press, app);
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

/*
** Bonus hook:
** mandatory keeps argv[1], bonus may replace it with the current level path.
*/
static int	resolve_start_map(t_app *app, const char *arg_path,
	const char **map_path)
{
	if (bonus_levels_init(app, arg_path) != 0)
		return (1);
	*map_path = bonus_level_current_path(app);
	if (*map_path == NULL)
		*map_path = arg_path;
	return (0);
}

int	main(int argc, char **argv)
{
	t_app		app;
	const char	*map_path;

	if (argc != 2)
		return (error_put("Error\nUsage: ./cub3D <map.cub>\n"), 1);
	init_app(&app);
	if (resolve_start_map(&app, argv[1], &map_path) != 0)
		return (free_app(&app), 1);
	if (parse_file(&app, map_path) != 0)
		return (free_app(&app), 1);
	init_player_vectors(&app);
	if (init_mlx(&app) != 0)
		return (free_app(&app), 1);
	if (start_game_loop(&app) != 0)
		return (free_app(&app), 1);
	free_app(&app);
	return (0);
}
