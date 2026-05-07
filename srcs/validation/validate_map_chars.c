/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <dbouizem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 20:22:12 by bbeceiro          #+#    #+#             */
/*   Updated: 2026/05/07 18:41:01 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Bonus hook:
** mandatory accepts only "01NSEW "; bonus may add extra map symbols.
*/
static int	is_valid_char(char c)
{
	if (ft_strchr("01NSEW ", c) != NULL)
		return (1);
	return (bonus_is_valid_map_char(c));
}

static int	check_all_chars(char **lines, int start)
{
	int	i;
	int	j;

	i = start;
	while (lines[i])
	{
		j = 0;
		while (lines[i][j])
		{
			if (!is_valid_char(lines[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	validate_chars(t_app *app, char **lines, int start)
{
	(void)app;
	if (check_all_chars(lines, start) != 0)
		return (error_put("Error\nMap contains invalid characters\n"), 1);
	return (0);
}
