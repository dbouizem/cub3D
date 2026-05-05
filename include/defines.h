/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 06:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/05/03 22:02:25 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

/*
** Window defaults.
*/
# define WIN_W	1280
# define WIN_H	720

/*
** Keyboard keycodes used by MLX on Linux/X11.
*/
# define KEY_ESC	65307
# define KEY_W	119
# define KEY_Z	122
# define KEY_A	97
# define KEY_Q	113
# define KEY_S	115
# define KEY_D	100
# define KEY_E	101
# define KEY_SPACE	32
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_F1	65470
# define KEY_F2	65471
# define KEY_F3	65472
# define KEY_F4	65473

/*
** MLX event identifiers.
*/
# define EVENT_KEYPRESS	2
# define EVENT_KEYRELEASE	3
# define EVENT_BUTTONPRESS	4
# define EVENT_MOUSEMOVE	6
# define EVENT_CONFIGURE	22
# define EVENT_DESTROY	17

/*
** Mouse button identifiers.
*/
# define BUTTON_SCROLL_UP	4
# define BUTTON_SCROLL_DOWN	5
# define BUTTON_LEFT	1

/*
** Parser status codes.
*/
# define PARSE_OK	0
# define PARSE_ERR	1
# define PARSE_NOT_HEADER	2

/*
** Gameplay tuning constants.
** MOVE_SPEED and ROT_SPEED are units/second and radians/second.
** COLLISION_RADIUS is the player capsule radius in map cells.
*/
# define FOV_FACTOR	0.66
# define FRAME_DT_DEFAULT	0.016666667
# define FRAME_DT_MAX	0.05
# define MOVE_SPEED	6.0
# define ROT_SPEED	4.8
# define COLLISION_RADIUS	0.15

#endif
