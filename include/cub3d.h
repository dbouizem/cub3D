/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 06:23:18 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/02 16:05:40 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "defines.h"
# include "structs.h"
# include "validation.h"
# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>

/* Parsing helpers: file I/O and line splitting. */
int		has_cub_extension(const char *path);
char	*read_all_text(const char *path);
int		count_lines(const char *text);
char	**split_lines(const char *text, int count);

/* Parsing helpers: header identifiers and values. */
int		is_empty_line(const char *line);
int		starts_with_id(const char *line, const char *id);
int		starts_with_one_id(const char *line, char id);
int		is_map_like_line(const char *line);
char	*dup_trimmed_value(const char *line, int start);
int		parse_texture(char **slot, const char *line);
int		parse_rgb_triplet(const char *line, int start, int out[3]);
int		parse_color(int dst[3], const char *line);
int		parse_headers(t_app *app, char **lines, int line_count, int *map_start);
int		check_required_headers(t_app *app);
int		validate_map_block(char **lines, int line_count, int map_start);
int		parse_header_entry(t_app *app, char *line);
int		starts_with_header_prefix(const char *line);
int		has_required_headers_loaded(t_app *app);

/* App lifecycle and rendering loop. */
int		parse_file(t_app *app, const char *path);
void	init_app(t_app *app);
int		init_mlx(t_app *app);
int		draw_frame(t_app *app);
int		close_window(t_app *app);
int		handle_keypress(int keycode, t_app *app);

/* Shared utilities. */
void	error_put(const char *msg);
void	free_split(char **ptr);
void	free_app(t_app *app);

#endif
