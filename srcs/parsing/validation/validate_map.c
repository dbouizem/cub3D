/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 20:34:08 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/03 13:08:26 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** @brief: Orchestrates all map validation checks in sequence.
** @param app: App struct containing player position and config
** @param lines: Array of map lines
** @param start: Index where map begins in lines array
** @return: 0 if all validations pass, 1 if any check fails
*/
int	validate_map(t_app *app, char **lines, int start)
{
	if (validate_player(app, lines, start) != 0)
		return (1);
	if (validate_boundaries(app, lines, start) != 0)
		return (1);
	if (validate_chars(app, lines, start) != 0)
		return (1);
	if (check_enclosure(app, lines, start) != 0)
		return (1);
	return (0);
}
