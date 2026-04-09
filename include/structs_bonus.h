/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 10:25:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/06 10:25:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

# define BONUS_HEADER_VERSION 1

typedef enum e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN,
	DOOR_CLOSING
}	t_door_state;

typedef struct s_door
{
	int				x;
	int				y;
	t_door_state	state;
	double			open_progress;
	double			state_timer;
}	t_door;

typedef struct s_bonus_doors
{
	t_door	*items;
	int		count;
	int		cap;
	double	interact_cooldown;
	double	interact_timer;
}	t_bonus_doors;

typedef t_bonus_doors	t_bdoor;

#endif
