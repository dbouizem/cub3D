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

# include "img.h"

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

typedef struct s_mm
{
	int	ox;
	int	oy;
	int	cx;
	int	cy;
	int	size;
	int	r2;
	int	ring2;
}	t_mm;

typedef struct s_bonus_assets
{
	t_img	walls[BONUS_WALL_COUNT];
	t_img	wall_symbols[BONUS_WALL_SYMBOL_COUNT];
	t_img	doors[BONUS_DOOR_COUNT];
	t_img	wall_o_anim[BONUS_ANIM_O_FRAMES];
	t_img	wall_p_anim[BONUS_ANIM_P_FRAMES];
	t_img	wall_q_anim[BONUS_ANIM_Q_FRAMES];
	t_img	wall_star_anim[BONUS_ANIM_STAR_FRAMES];
	t_img	wall_dot_anim[BONUS_ANIM_DOT_FRAMES];
	t_img	wall_lparen_anim[BONUS_ANIM_LPAREN_FRAMES];
}	t_bonus_assets;

typedef struct s_bonus_retro
{
	t_img	fb;
	t_img	out;
	t_img	minimap;
	int		enabled;
	double	minimap_zoom;
}	t_bonus_retro;

typedef struct s_bonus_levels
{
	const char	*paths[BONUS_LEVEL_MAX];
	const char	*start_path;
	int			count;
	int			current;
	int			active;
}	t_bonus_levels;

typedef struct s_bonus_sprites
{
	t_img	star_tex;
	t_img	at_tex;
	t_img	*tex_of;
	double	*xs;
	double	*ys;
	char	*types;
	double	*dists;
	int		count;
	int		cap;
	double	*zbuf;
	int		zcap;
}	t_bonus_sprites;

typedef struct s_sprite_proj
{
	int		sx;
	int		sh;
	int		x0;
	int		x1;
	int		y0;
	int		y1;
	double	sy;
}	t_sprite_proj;

typedef struct s_bonus_ctx
{
	t_bonus_assets	assets;
	t_bonus_retro	retro;
	t_bonus_doors	doors;
	t_bonus_levels	levels;
	t_bonus_sprites	sprites;
}	t_bonus_ctx;

#endif
