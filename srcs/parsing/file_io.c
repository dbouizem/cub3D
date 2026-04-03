/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_io.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:59:21 by dbouizem          #+#    #+#             */
/*   Updated: 2026/03/31 16:59:22 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>

int	has_cub_extension(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	return (ft_strncmp(path + len - 4, ".cub", 4) == 0);
}

static int	ensure_capacity(char **text, size_t *cap, size_t len, size_t needed)
{
	char	*out;
	size_t	new_cap;

	if (*cap >= needed)
		return (0);
	new_cap = *cap;
	if (new_cap == 0)
		new_cap = 4096;
	while (new_cap < needed && new_cap <= ((size_t) - 1) / 2)
		new_cap *= 2;
	if (new_cap < needed)
		return (1);
	out = malloc(new_cap);
	if (!out)
		return (1);
	if (len > 0 && *text)
		ft_memcpy(out, *text, len);
	free(*text);
	*text = out;
	*cap = new_cap;
	return (0);
}

static int	read_chunks(int fd, char **text, size_t *len, size_t *cap)
{
	ssize_t	br;
	char	buf[4096];

	br = read(fd, buf, sizeof(buf));
	while (br > 0)
	{
		if ((size_t)br > (size_t) - 1 - *len - 1)
			return (1);
		if (ensure_capacity(text, cap, *len, *len + (size_t)br + 1) != 0)
			return (1);
		ft_memcpy(*text + *len, buf, (size_t)br);
		*len += (size_t)br;
		br = read(fd, buf, sizeof(buf));
	}
	return (br < 0);
}

char	*read_all_text(const char *path)
{
	int		fd;
	char	*text;
	size_t	len;
	size_t	cap;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	text = NULL;
	len = 0;
	cap = 0;
	if (read_chunks(fd, &text, &len, &cap) != 0)
		return (free(text), close(fd), NULL);
	close(fd);
	if (!text)
	{
		text = malloc(1);
		if (!text)
			return (NULL);
		text[0] = '\0';
	}
	else
		text[len] = '\0';
	return (text);
}

int	count_lines(const char *text)
{
	size_t	count;
	size_t	i;

	if (!text || text[0] == '\0')
		return (0);
	count = 1;
	i = 0;
	while (text[i])
	{
		if (text[i] == '\n')
		{
			if (count == (size_t)INT_MAX)
				return (-1);
			count++;
		}
		i++;
	}
	if (i > 0 && text[i - 1] == '\n')
		count--;
	if (count > (size_t)INT_MAX)
		return (-1);
	return ((int)count);
}
