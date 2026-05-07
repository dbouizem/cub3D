/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeceiro <bbeceiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:34:31 by bbeceiro          #+#    #+#             */
/*   Updated: 2026/05/07 14:34:33 by bbeceiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_map(t_app *app, char **lines, int start)
{
	if (validate_player(app, lines, start) != 0)
		return (1);
	if (validate_chars(app, lines, start) != 0)
		return (1);
	if (check_enclosure(app, lines, start) != 0)
		return (1);
	return (0);
}
