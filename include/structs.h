/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 06:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/05/06 14:57:47 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "structs_bonus.h"

typedef unsigned long	t_size;

/*
** Player state read from the map.
** x/y are stored as doubles because movement happens between map cells.
** orientation is the original N/S/E/W character found in the .cub map.
*/
typedef struct s_player
{
	double	x;
	double	y;
	char	orientation;
}	t_player;

/*
** Parsed map block.
** grid is the array of map lines kept after header parsing and validation.
** height is the number of map rows.
*/
typedef struct s_map
{
	char	**grid;
	int		height;
}	t_map;

/*
** Parsed .cub header configuration.
** tex_* are file paths read from NO/SO/WE/EA entries, not loaded images.
** floor_rgb and ceiling_rgb keep the raw R,G,B values read from F and C.
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
** Current input state.
** Key hooks set these flags to 1 or 0, then the frame update uses them
** to move or rotate the player continuously.
** mouse_dx is the horizontal mouse movement since the last mouse event.
** mouse_last_x/mouse_ready avoid a jump on the first mouse event.
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
** Temporary parser context for the .cub header phase.
** lines contains the whole file split into strings.
** line_count is the number of lines in that array.
** map_start receives the index where the map block begins.
** map_path is used to resolve texture paths relative to the .cub file.
*/
typedef struct s_parse_headers
{
	char		**lines;
	int			line_count;
	int			*map_start;
	const char	*map_path;
}	t_parse_headers;

/*
** Raycasting state for one vertical screen column.
** x is the current screen column.
** camera_x maps x into camera space, usually between -1 and 1.
** ray_dir_x/y is the direction of the ray launched from the player.
** map_x/y is the current map cell crossed by the ray.
** delta_x/y is the distance needed to cross one map cell on each axis.
** side_x/y is the distance to the next grid side on each axis.
** step_x/y is the DDA direction, either -1 or 1.
** side tells whether the hit happened on an X side or a Y side.
** perp_dist is the corrected wall distance used to avoid fisheye.
** line_height, draw_start and draw_end define the wall slice to draw.
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
** Main application state shared by all systems.
** config stores parsed .cub paths and RGB values.
** map stores the validated map grid.
** player stores the player position and initial orientation.
** mlx_ptr is the MiniLibX connection returned by mlx_init().
** win_ptr is the window returned by mlx_new_window().
** frame is the image buffer drawn every frame, sized from the window.
** tex_no/so/we/ea are the loaded XPM images used for wall rendering.
** win_w/win_h store the current window size.
** floor_color/ceiling_color are RGB colors converted to drawable ints.
** delta_time is the elapsed time between two frames.
** last_frame_time is used to calculate delta_time.
** frame_count is incremented each rendered frame.
** dir_x/dir_y is the player view direction.
** plane_x/plane_y is the camera plane used for the field of view.
** input stores the current keyboard and mouse state.
** bonus stores bonus-only state. In mandatory builds, the Makefile links
** no-op bonus functions, so this field is initialized but not actively used.
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
** Breadth-first search context used to validate that the map is closed.
** lines/start point to the map block inside the full split .cub file.
** width/height are the calculated map bounds.
** visited marks open cells already reached by the BFS.
** qx/qy are the BFS queue coordinates.
** qcap is the queue capacity, head is the read index, tail the write index.
** px/py is the player cell used as the BFS starting point.
** leak becomes 1 if the search reaches outside the map or a space.
** alloc_fail becomes 1 if queue/visited allocation fails.
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
