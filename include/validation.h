/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 20:14:37 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/02 12:07:52 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

struct	s_app;

/* validate_map.c - Main orchestrator */
int	validate_map(struct s_app *app, char **lines, int start);

/* validate_player.c - Player count validation (only 1) */
int	validate_player(struct s_app *app, char **lines, int start);

/* validate_boundaries.c - Wall enclousure check */
int	validate_boundaries(struct s_app *app, char **lines, int start);

/* validate_chars.c - Character validation */
int validate_chars(struct s_app *app, char **lines, int start);

#endif
