/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_map_noop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 20:20:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/05/06 16:35:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Mandatory mode uses only the .cub path passed by the user.
*/
int	bonus_levels_init(t_app *app, const char *start_path)
{
	(void)app;
	(void)start_path;
	return (0);
}

/*
** Returning NULL tells main() to keep argv[1] as the map path.
*/
const char	*bonus_level_current_path(t_app *app)
{
	(void)app;
	return (NULL);
}

/*
** Level switching is disabled in mandatory mode.
*/
int	bonus_load_next_level(t_app *app)
{
	(void)app;
	return (1);
}

/*
** Shared map accessor: outside or missing cells are treated as spaces.
*/
char	bonus_map_cell_at(t_app *app, int x, int y)
{
	int	len;

	if (!app || !app->map.grid || y < 0 || y >= app->map.height)
		return (' ');
	len = (int)ft_strlen(app->map.grid[y]);
	if (x < 0 || x >= len)
		return (' ');
	return (app->map.grid[y][x]);
}

/*
** The minimap is a bonus feature, so mandatory mode draws nothing here.
*/
void	bonus_draw_minimap(t_app *app)
{
	(void)app;
}
