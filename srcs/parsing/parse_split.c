/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/03 00:00:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*dup_until_newline(const char *text, size_t *idx)
{
	size_t	start;
	size_t	len;
	char	*out;

	start = *idx;
	while (text[*idx] && text[*idx] != '\n')
		(*idx)++;
	len = *idx - start;
	out = malloc(len + 1);
	if (!out)
		return (NULL);
	ft_memcpy(out, text + start, len);
	out[len] = '\0';
	if (text[*idx] == '\n')
		(*idx)++;
	return (out);
}

char	**split_lines(const char *text, int count)
{
	char	**out;
	size_t	i;
	int		line;

	if (count < 0)
		return (NULL);
	if ((size_t)count > (SIZE_MAX / sizeof(char *)) - 1)
		return (NULL);
	out = malloc(sizeof(char *) * (count + 1));
	if (!out)
		return (NULL);
	i = 0;
	line = 0;
	while (line < count)
	{
		out[line] = dup_until_newline(text, &i);
		if (!out[line])
			return (out[line] = NULL, free_split(out), NULL);
		line++;
	}
	out[line] = NULL;
	return (out);
}
