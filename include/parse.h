/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 06:27:42 by dbouizem          #+#    #+#             */
/*   Updated: 2026/03/31 17:09:31 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define PARSE_OK 0
# define PARSE_ERR 1
# define PARSE_NOT_HEADER 2

struct s_app;

int		has_cub_extension(const char *path);
char	*read_all_text(const char *path);
int		count_lines(const char *text);
char	**split_lines(const char *text, int count);

int		is_empty_line(const char *line);
int		starts_with_id(const char *line, const char *id);
int		starts_with_one_id(const char *line, char id);
int		is_map_like_line(const char *line);
char	*dup_trimmed_value(const char *line, int start);
int		parse_texture(char **slot, const char *line);
int		parse_rgb_triplet(const char *line, int start, int out[3]);
int		parse_color(int dst[3], const char *line);

int		parse_headers(struct s_app *app, char **lines, int line_count,
			int *map_start);
int		check_required_headers(struct s_app *app);

#endif
