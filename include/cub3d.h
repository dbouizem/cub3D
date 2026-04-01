/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 06:23:18 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/01 20:19:59 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "parse.h"
# include "validation.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_config
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
}	t_config;

typedef struct s_app
{
	t_config	config;
	char		**file_lines;
	int			line_count;
	int			map_start;
}	t_app;

int		parse_file(t_app *app, const char *path);
void	init_app(t_app *app);

void	error_put(const char *msg);
void	free_split(char **ptr);
void	free_app(t_app *app);

#endif
