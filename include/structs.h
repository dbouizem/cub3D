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

# include "structs_bonus.h"

typedef unsigned long	t_size;

/*
** Player map position and initial orientation from the .cub file.
*/
typedef struct s_player
{
	double	x;
	double	y;
	char	orientation;
}	t_player;

/*
** Rectangular map grid after parsing.
*/
typedef struct s_map
{
	char	**grid;
	int		height;
}	t_map;

/*
** Parsed .cub configuration: mandatory texture paths and RGB colors.
*/
typedef struct s_config
{
	char	*tex_no;
	char	*tex_so;
	char	*tex_we;
	char	*tex_ea;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
}	t_config;

/*
** Keyboard and mouse state accumulated between frames.
*/
typedef struct s_input
{
	int	forward;
	int	backward;
	int	left;
	int	right;
	int	turn_left;
	int	turn_right;
	int	mouse_dx;
	int	mouse_last_x;
	int	mouse_ready;
}	t_input;

/*
** Parser context used while reading header entries before the map.
*/
typedef struct s_parse_headers
{
	char		**lines;
	int			line_count;
	int			*map_start;
	const char	*map_path;
}	t_parse_headers;

/*
** Raycasting state for one screen column.
*/
typedef struct s_ray
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

/*
** Main application state shared by parsing, MLX, rendering, and bonus systems.
*/
typedef struct s_app
{
	t_config	config;
	t_map		map;
	t_player	player;
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
	double		delta_time;
	double		last_frame_time;
	t_size		frame_count;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	t_input		input;
	t_bonus_ctx	bonus;
}	t_app;

/*
** Breadth-first search context used by closed-map validation.
*/
typedef struct s_bfs_context
{
	char	**lines;
	int		start;
	int		width;
	int		height;
	char	**visited;
	int		*qx;
	int		*qy;
	t_size	qcap;
	t_size	head;
	t_size	tail;
	int		px;
	int		py;
	int		leak;
	int		alloc_fail;
}	t_bfs_context;

#endif
