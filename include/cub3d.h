/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 06:23:18 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/05 05:20:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "defines.h"
# include "defines_bonus.h"
# include "structs.h"
# include "cub3d_bonus.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

/*
** File reading and line splitting.
*/
int		has_cub_extension(const char *path);
char	*read_all_text(const char *path);
int		count_lines(const char *text);
char	**split_lines(const char *text, int count);

/*
** Config parsing helpers.
*/
int		is_empty_line(const char *line);
int		starts_with_id(const char *line, const char *id);
int		starts_with_one_id(const char *line, char id);
int		is_map_like_line(const char *line);
char	*dup_trimmed_value(const char *line, int start);

/*
** Header parsers.
*/
int		parse_texture(char **slot, const char *line, const char *map_path);
int		parse_rgb_triplet(const char *line, int start, int out[3]);
int		parse_color(int dst[3], const char *line);

int		parse_headers(t_app *app, t_parse_headers *ctx);
int		check_required_headers(t_app *app);
int		parse_header_entry(t_app *app, char *line, const char *map_path);
int		starts_with_header_prefix(const char *line);
int		has_required_headers_loaded(t_app *app);
int		parse_map(t_app *app, char **lines, int start_idx, int line_count);

/*
** Map validation.
*/
int		validate_map(t_app *app, char **lines, int start);
int		validate_player(t_app *app, char **lines, int start);
int		validate_chars(t_app *app, char **lines, int start);
int		is_open_cell(char c);
void	init_directions(int *dx, int *dy);
int		check_enclosure(t_app *app, char **lines, int start);
int		init_bfs_context(t_bfs_context *ctx, t_app *app, char **lines,
			int start);
int		finish_validation(t_bfs_context *ctx, const char *msg);
int		find_player(t_app *app, char **lines, int start);
int		calculate_dimensions(char **lines, int start, int *width, int *height);
char	**allocate_visited(int height, int width);
int		scan_unreachable(char **lines, int start, int height, char **visited);
void	cleanup_visited(char **visited, int height);

/*
** Application and MLX lifecycle.
*/
int		parse_file(t_app *app, const char *path);
void	init_app(t_app *app);
void	init_player_vectors(t_app *app);
int		init_mlx(t_app *app);

/*
** Rendering.
*/
int		draw_frame(t_app *app);
void	update_frame_timing(t_app *app);
int		raycast_scene(t_app *app);
t_ray	cast_ray(t_app *app, int x);
void	draw_wall_column(t_app *app, t_ray ray);

/*
** Input, window hooks, movement, and rotation.
*/
int		handle_keypress(int keycode, t_app *app);
int		handle_keyrelease(int keycode, t_app *app);
int		handle_mouse_press(int button, int x, int y, t_app *app);
int		handle_mouse_move(int x, int y, t_app *app);
int		close_window(t_app *app);
void	update_player_input(t_app *app);
void	apply_mouse_look(t_app *app);
void	bind_window_hooks(t_app *app);
int		resize_window(t_app *app, int w, int h, int recreate_window);
int		apply_resolution_preset(t_app *app, int keycode);
void	move_with_collision(t_app *app, double dx, double dy);
void	move_forward(t_app *app);
void	move_backward(t_app *app);
void	strafe_left(t_app *app);
void	strafe_right(t_app *app);
void	rotate_left(t_app *app);
void	rotate_right(t_app *app);

/*
** Generic utilities.
*/
void	error_put(const char *msg);
void	free_split(char **ptr);
void	free_app(t_app *app);
void	put_pixel(t_img *img, int x, int y, int color);
void	apply_world_vignette(t_app *app);

#endif
