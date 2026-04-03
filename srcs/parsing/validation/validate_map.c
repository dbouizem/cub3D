/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 20:34:08 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/02 16:57:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
