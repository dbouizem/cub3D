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

int	main(int argc, char **argv)
{
	t_app	app;

	if (argc != 2)
		return (error_put("Error\nUsage: ./cub3D <map.cub>\n"), 1);
	init_app(&app);
	if (parse_file(&app, argv[1]) != 0)
		return (free_app(&app), 1);
	free_app(&app);
	return (0);
}
