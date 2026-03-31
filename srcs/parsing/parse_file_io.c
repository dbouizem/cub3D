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

int	has_cub_extension(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	return (ft_strncmp(path + len - 4, ".cub", 4) == 0);
}

static char	*append_chunk(char *dst, size_t dst_len,
	const char *src, size_t src_len)
{
	char	*out;

	out = malloc(dst_len + src_len + 1);
	if (!out)
		return (free(dst), NULL);
	if (dst_len > 0)
		ft_memcpy(out, dst, dst_len);
	if (src_len > 0)
		ft_memcpy(out + dst_len, src, src_len);
	out[dst_len + src_len] = '\0';
	free(dst);
	return (out);
}

static char	*finish_read(int fd, char *text, ssize_t br)
{
	close(fd);
	if (br < 0)
		return (free(text), NULL);
	if (!text)
		return (append_chunk(NULL, 0, "", 0));
	return (text);
}

char	*read_all_text(const char *path)
{
	int		fd;
	ssize_t	br;
	char	*text;
	char	buf[4096];
	size_t	len;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	text = NULL;
	len = 0;
	br = read(fd, buf, sizeof(buf));
	while (br > 0)
	{
		text = append_chunk(text, len, buf, (size_t)br);
		if (!text)
			return (close(fd), NULL);
		len += (size_t)br;
		br = read(fd, buf, sizeof(buf));
	}
	return (finish_read(fd, text, br));
}

int	count_lines(const char *text)
{
	int		count;
	size_t	i;

	if (!text || text[0] == '\0')
		return (0);
	count = 1;
	i = 0;
	while (text[i])
	{
		if (text[i] == '\n')
			count++;
		i++;
	}
	if (i > 0 && text[i - 1] == '\n')
		count--;
	return (count);
}
