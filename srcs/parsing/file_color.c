/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:59:03 by dbouizem          #+#    #+#             */
/*   Updated: 2026/03/31 16:59:04 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_number(const char *line, int *idx, int *value)
{
	int	val;
	int	digit;

	if (!ft_isdigit(line[*idx]))
		return (1);
	val = 0;
	while (ft_isdigit(line[*idx]))
	{
		digit = line[*idx] - '0';
		if (val > 25 || (val == 25 && digit > 5))
			return (1);
		val = val * 10 + digit;
		(*idx)++;
	}
	*value = val;
	return (0);
}

static int	parse_separator(const char *line, int *idx, int has_next)
{
	while (line[*idx] && ft_isspace(line[*idx]))
		(*idx)++;
	if (has_next && line[(*idx)++] != ',')
		return (1);
	while (line[*idx] && ft_isspace(line[*idx]))
		(*idx)++;
	return (0);
}

int	parse_rgb_triplet(const char *line, int start, int out[3])
{
	int	i;
	int	k;

	i = start;
	while (line[i] && ft_isspace(line[i]))
		i++;
	k = 0;
	while (k < 3)
	{
		if (parse_number(line, &i, &out[k]) != 0)
			return (1);
		if (parse_separator(line, &i, k < 2) != 0)
			return (1);
		k++;
	}
	while (line[i])
		if (!ft_isspace(line[i++]))
			return (1);
	return (0);
}

int	parse_color(int dst[3], const char *line)
{
	int	i;
	int	tmp[3];

	if (dst[0] != -1 || dst[1] != -1 || dst[2] != -1)
		return (error_put("Error\nDuplicate color identifier\n"), 1);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (parse_rgb_triplet(line, i + 1, tmp) != 0)
		return (error_put("Error\nInvalid RGB color format\n"), 1);
	dst[0] = tmp[0];
	dst[1] = tmp[1];
	dst[2] = tmp[2];
	return (0);
}
