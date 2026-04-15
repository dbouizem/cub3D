/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 06:23:18 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/14 16:35:26 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "defines.h"
# include "structs.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

/* Core */
void	init_app(t_app *app);
int		init_mlx(t_app *app);
int		parse_file(t_app *app, const char *path);

/* Input */
int		key_press(int keycode, t_app *app);
int		key_release(int keycode, t_app *app);
int		close_window(t_app *app);

/* Movement / rotation */
void	handle_movement(t_app *app);
void	handle_rotation(t_app *app);

/* Render */
int		draw_frame(t_app *app);
void	put_pixel(t_img *img, int x, int y, int color);
void	clear_frame(t_app *app);
char	get_map_cell(t_app *app, int map_x, int map_y);
void	init_ray(t_app *app, t_ray *ray, int x);
void	prepare_dda(t_app *app, t_ray *ray);
void	trace_ray(t_app *app, t_ray *ray);
void	calculate_ray_result(t_app *app, t_ray *ray);
void	draw_wall_column(t_app *app, t_ray *ray, int x);
void	render_rays(t_app *app);

/* Parsing - file */
int		has_cub_extension(const char *path);
char	*read_all_text(const char *path);
int		count_lines(const char *text);
char	**split_lines(const char *text, int count);

/* Parsing - lines */
int		is_empty_line(const char *line);
int		starts_with_id(const char *line, const char *id);
int		starts_with_one_id(const char *line, char id);
int		is_map_like_line(const char *line);
char	*dup_trimmed_value(const char *line, int start);

/* Parsing - config */
int		parse_texture(char **slot, const char *line);
int		parse_rgb_triplet(const char *line, int start, int out[3]);
int		parse_color(int dst[3], const char *line);
int		parse_headers(t_app *app, char **lines,
			int line_count, int *map_start);
int		check_required_headers(t_app *app);
int		parse_header_entry(t_app *app, char *line);
int		has_required_headers_loaded(t_app *app);
int		starts_with_header_prefix(const char *line);

/* Validation - map */
int		validate_map(t_app *app, char **lines, int start);
int		validate_player(t_app *app, char **lines, int start);
int		validate_chars(t_app *app, char **lines, int start);
int		check_enclosure(t_app *app, char **lines, int start);

/* Validation - player */
void	init_player_directions(t_app *app);

/* Validation - bfs */
int		find_player(t_app *app, char **lines, int start);
int		calculate_dimensions(char **lines, int start,
			int *width, int *height);
char	**allocate_visited(int height, int width);
int		scan_unreachable(char **lines, int start,
			int height, char **visited);
void	cleanup_visited(char **visited, int height);
void	enqueue(t_node **queue, int x, int y);
int		dequeue(t_node **queue, int *x, int *y);
void	free_queue(t_node *queue);
void	init_directions(int *dx, int *dy);

/* Utilities */
void	error_put(const char *msg);
void	free_split(char **ptr);
void	free_app(t_app *app);

#endif
