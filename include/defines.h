/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeceiro <bbeceiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 14:29:14 by bbeceiro          #+#    #+#             */
/*   Updated: 2026/05/07 14:29:16 by bbeceiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/* Boolean helpers */
# define FALSE 0
# define TRUE 1

/* Movement and rotation speeds */
# define MOVE_SPEED 0.09
# define ROT_SPEED 0.05
# define PLAYER_RADIUS 0.2

/* Window and event constants (Linux/X11 key/event codes). */
# define WIN_W 1280
# define WIN_H 720
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Z 122
# define KEY_Q 113
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define EVENT_KEYPRESS 2
# define EVENT_KEYRELEASE 3
# define EVENT_DESTROY 17

/* Generic parser return codes. */
# define PARSE_OK 0
# define PARSE_ERR 1
# define PARSE_NOT_HEADER 2

#endif
