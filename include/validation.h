/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 20:14:37 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/03 11:00:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# include "structs.h"

/* validate_map.c - Main orchestrator */
int		validate_map(t_app *app, char **lines, int start);

/* validate_player.c - Player count validation (only 1) */
int		validate_player(t_app *app, char **lines, int start);

/* validate_boundaries.c - Wall enclosure check */
int		validate_boundaries(t_app *app, char **lines, int start);

/* validate_chars.c - Character validation */
int		validate_chars(t_app *app, char **lines, int start);

/* flood_fill_utils.c - Queue operations */
void	enqueue(t_node **queue, int x, int y);
int		dequeue(t_node **queue, int *x, int *y);
void	free_queue(t_node *queue);
void	init_directions(int *dx, int *dy);

/* flood_fill_bfs.c */
int		check_enclosure(t_app *app, char **lines, int start);

/* flood_fill_core.c */
int		find_player(t_app *app, char **lines, int start);
int		calculate_dimensions(char **lines, int start, int *width, int *height);
char	**allocate_visited(int height, int width);
int		scan_unreachable(char **lines, int start, int height, char **visited);
void	cleanup_visited(char **visited, int height);

#endif
