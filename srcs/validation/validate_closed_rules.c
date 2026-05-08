/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_closed_rules.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <dbouizem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 00:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/05/08 00:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_validation_door(char cell)
{
	return (ft_strchr(BONUS_DOOR_SET, cell) != NULL);
}

int	is_validation_wall(char cell)
{
	if (is_validation_door(cell))
		return (0);
	return (bonus_is_solid_tile(cell));
}

int	mark_validation_leak(t_bfs_context *ctx, char cell)
{
	if (!is_validation_door(cell))
		ctx->leak = 1;
	return (0);
}
