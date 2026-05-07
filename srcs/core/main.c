/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:00:15 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/06 11:28:08 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	start_game_loop(t_app *app)
{
	mlx_hook(app->win_ptr, EVENT_KEYPRESS, 1L << 0,
		(int (*)())key_press, app);
	mlx_hook(app->win_ptr, EVENT_DESTROY, 0, (int (*)())close_window, app);
	mlx_loop_hook(app->mlx_ptr, (int (*)())draw_frame, app);
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
	if (init_mlx(&app) != 0)
		return (free_app(&app), 1);
	if (start_game_loop(&app) != 0)
		return (free_app(&app), 1);
	free_app(&app);
	return (0);
}
