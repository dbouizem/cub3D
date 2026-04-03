/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 06:23:18 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/03 13:39:29 by brrr1            ###   ########.fr       */
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

/* ************************************************************************** */
/*                                Structs                                     */
/* ************************************************************************** */

/* Configuration: textures and colors */
typedef struct s_config
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
}	t_config;

/* Main application context: holds config, raw file lines, and player data */
typedef struct s_app
{
	t_config	config;
	char		**file_lines;
	int			line_count;
	int			map_start;
	int			player_x;
	int			player_y;
	char		player_dir;
}	t_app;

/* Linked list node for BFS queue */
typedef struct s_node
{
	int				x;
	int				y;
	struct s_node	*next;
}	t_node;

/* Context for BFS flood-fill algorithm */
typedef struct s_bfs_context
{
	char	**lines;
	int		start;
	int		width;
	int		height;
	char	**visited;
	t_node	*queue;
	int		px;
	int		py;
}	t_bfs_context;

/* ************************************************************************** */
/*                      Initialization and Parsing                            */
/* ************************************************************************** */
int		parse_file(t_app *app, const char *path);
void	init_app(t_app *app);

/* ************************************************************************** */
/*                    Utilities and Memory Management                         */
/* ************************************************************************** */
void	error_put(const char *msg);
void	free_split(char **ptr);
void	free_app(t_app *app);

#endif
