/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 20:34:08 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/01 20:46:47 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	validate_map(t_app *app, char **lines, int start)
{
	// 1. Check player count
	if (validate_player(app, lines, start) != 0)
		return (1);
	// 2. Check boundaries

	// 3. Check characters
	return (0);
}
