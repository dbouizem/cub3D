/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_assets.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 18:40:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 18:40:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_readable_file(const char *path)
{
	int	fd;

	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

static char	*extract_dirname(const char *path)
{
	char	*last;

	if (!path)
		return (NULL);
	last = ft_strrchr(path, '/');
	if (!last)
		return (ft_strdup("."));
	if (last == path)
		return (ft_strdup("/"));
	return (ft_substr(path, 0, (size_t)(last - path)));
}

static int	step_to_parent(char *dir)
{
	char	*last;

	if (!dir || !*dir)
		return (0);
	if (ft_strcmp(dir, "/") == 0 || ft_strcmp(dir, ".") == 0)
		return (0);
	last = ft_strrchr(dir, '/');
	if (!last)
		return (dir[0] = '.', dir[1] = '\0', 1);
	if (last == dir)
		return (dir[1] = '\0', 1);
	*last = '\0';
	return (1);
}

static char	*resolve_from_map_chain(t_app *app, const char *path)
{
	const char	*map_path;
	char		*dir;
	char		*candidate;
	int			steps;

	map_path = bonus_level_current_path(app);
	if (!map_path)
		map_path = app->bonus.levels.start_path;
	dir = extract_dirname(map_path);
	if (!dir)
		return (NULL);
	steps = 0;
	while (steps++ < 8)
	{
		candidate = ft_strjoin3(dir, "/", path);
		if (candidate && is_readable_file(candidate))
			return (free(dir), candidate);
		free(candidate);
		if (!step_to_parent(dir))
			break ;
	}
	return (free(dir), NULL);
}

char	*bonus_resolve_asset_path(t_app *app, const char *path)
{
	if (is_readable_file(path))
		return (ft_strdup(path));
	if (!app || !path || path[0] == '/')
		return (NULL);
	return (resolve_from_map_chain(app, path));
}
