/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 06:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/02 06:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* Generic image container for frame buffer and textures. */
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_node
{
	int				x;
	int				y;
	struct s_node	*next;
}	t_node;

/* Parsed .cub configuration (textures and RGB colors). */
typedef struct s_config
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
}	t_config;

/* Global application state shared across modules. */
typedef struct s_app
{
	t_config	config;
	char		**file_lines;
	int			line_count;
	int			map_start;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		frame;
	t_img		tex_no;
	t_img		tex_so;
	t_img		tex_we;
	t_img		tex_ea;
	int			win_w;
	int			win_h;
	int			floor_color;
	int			ceiling_color;
	int			player_x;
	int			player_y;
	char		player_dir;
}	t_app;

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
	int		leak;
}	t_bfs_context;

#endif
