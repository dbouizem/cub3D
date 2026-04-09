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

typedef struct s_player
{
	double	x;
	double	y;
	char	orientation;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		height;
}	t_map;

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

typedef struct s_parse_headers
{
	char		**lines;
	int			line_count;
	int			*map_start;
	const char	*map_path;
}	t_parse_headers;

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
	t_img		bonus_walls[BONUS_WALL_COUNT];
	t_img		bonus_wall_symbols[BONUS_WALL_SYMBOL_COUNT];
	t_img		bonus_doors[BONUS_DOOR_COUNT];
	t_img		bonus_wall_o_anim[BONUS_ANIM_O_FRAMES];
	t_img		bonus_wall_p_anim[BONUS_ANIM_P_FRAMES];
	t_img		bonus_wall_q_anim[BONUS_ANIM_Q_FRAMES];
	t_img		bonus_wall_star_anim[BONUS_ANIM_STAR_FRAMES];
	t_img		bonus_wall_dot_anim[BONUS_ANIM_DOT_FRAMES];
	t_img		bonus_wall_lparen_anim[BONUS_ANIM_LPAREN_FRAMES];
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
	t_img		bonus_fb;
	t_img		bonus_out;
	int			bonus_on;

	t_bdoor		bonus_door_sys;
}	t_app;

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
