/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:59:31 by dbouizem          #+#    #+#             */
/*   Updated: 2026/03/31 16:59:32 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_empty_line(const char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	starts_with_id(const char *line, const char *id)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (ft_strlen(line + i) < 3)
		return (0);
	if (ft_strncmp(line + i, id, 2) != 0)
		return (0);
	if (!ft_isspace(line[i + 2]))
		return (0);
	return (1);
}

int	starts_with_one_id(const char *line, char id)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (ft_strlen(line + i) < 2)
		return (0);
	if (line[i] != id)
		return (0);
	if (!ft_isspace(line[i + 1]))
		return (0);
	return (1);
}

int	is_map_like_line(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (0);
	while (line[i])
	{
		if (!ft_strchr(" 01NSEW", line[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*dup_trimmed_value(const char *line, int start)
{
	char	*out;

	out = ft_strtrim(line + start, " \t\n\r\v\f");
	if (!out)
		return (NULL);
	if (out[0] == '\0')
	{
		free(out);
		return (NULL);
	}
	return (out);
}
