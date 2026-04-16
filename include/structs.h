/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 06:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/14 16:41:37 by brrr1            ###   ########.fr       */
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

/* Key state tracker for player input */
typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	wall_x;
	char	wall_face;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

/* Global application state shared across modules. */
typedef struct s_app
{
	t_config	config;
	char		**file_lines;
	int			line_count;
	int			map_start;
	int			map_width;
	int			map_height;
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
	t_keys		keys;
	double		player_x;
	double		player_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
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
	t_node	*queue_tail;
	int		px;
	int		py;
	int		leak;
	int		alloc_error;
}	t_bfs_context;

#endif
