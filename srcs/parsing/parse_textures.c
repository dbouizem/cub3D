/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <dbouizem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by bbeceiro          #+#    #+#             */
/*   Updated: 2026/05/07 18:39:37 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*extract_base_dir(const char *path)
{
	char	*last_slash;

	if (path == NULL)
		return (NULL);
	last_slash = ft_strrchr(path, '/');
	if (last_slash == NULL)
		return (ft_strdup("."));
	if (last_slash == path)
		return (ft_strdup("/"));
	return (ft_substr(path, 0, (size_t)(last_slash - path)));
}

static char	*join_base_and_value(const char *base, const char *value)
{
	if (base == NULL || value == NULL)
		return (NULL);
	return (ft_strjoin3(base, "/", value));
}

static int	is_valid_xpm_path(const char *path)
{
	size_t	len;
	int		fd;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strncmp(path + len - 4, ".xpm", 4) == 0)
	{
		fd = open(path, O_RDONLY);
		if (fd < 0)
			return (0);
		close(fd);
		return (1);
	}
	return (0);
}

static char	*resolve_texture_candidate(const char *value, const char *map_path)
{
	char	*base;
	char	*candidate;

	if (value[0] == '/' && is_valid_xpm_path(value))
		return (ft_strdup(value));
	base = extract_base_dir(map_path);
	candidate = join_base_and_value(base, value);
	if (candidate && is_valid_xpm_path(candidate))
		return (free(base), candidate);
	free(base);
	free(candidate);
	return (NULL);
}

int	parse_texture(char **slot, const char *line, const char *map_path)
{
	int		i;
	char	*value;
	char	*resolved;

	if (*slot)
		return (error_put("Error\nDuplicate texture identifier\n"), 1);
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	value = dup_trimmed_value(line, i + 2);
	if (value == NULL)
		return (error_put("Error\nMissing texture path\n"), 1);
	resolved = resolve_texture_candidate(value, map_path);
	if (resolved)
		return (free(value), *slot = resolved, 0);
	if (ft_strrchr(value, '.')
		&& ft_strncmp(ft_strrchr(value, '.'), ".xpm", 4) == 0)
		error_put("Error\nTexture path is invalid or unreadable\n");
	else
		error_put("Error\nTexture must be an .xpm file\n");
	free(value);
	return (1);
}
