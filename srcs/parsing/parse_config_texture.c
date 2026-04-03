/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/03 00:00:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	valid_texture_path(const char *path)
{
	size_t	len;
	int		fd;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (error_put("Error\nTexture must be an .xpm file\n"), 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_put("Error\nTexture path is invalid or unreadable\n"), 1);
	close(fd);
	return (0);
}

int	parse_texture(char **slot, const char *line)
{
	int		i;
	char	*value;

	if (*slot)
		return (error_put("Error\nDuplicate texture identifier\n"), 1);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	value = dup_trimmed_value(line, i + 2);
	if (!value)
		return (error_put("Error\nMissing texture path\n"), 1);
	if (valid_texture_path(value) != 0)
		return (free(value), 1);
	*slot = value;
	return (0);
}
