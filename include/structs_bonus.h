/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 10:25:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/05/05 14:22:17 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

# include "defines_bonus.h"

# define BONUS_HEADER_VERSION 1

/*
** Generic MLX image buffer shared by mandatory and bonus code.
** img_ptr is the MLX image handle, addr is the raw pixel memory.
** width/height are in pixels, bpp is bits per pixel, line_len is the
** byte size of one image row, and endian describes byte order.
*/
typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

/*
** Doors are stored separately from the map so their animation state can change.
*/
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

/*
** Minimap and HUD drawing helpers.
*/
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

typedef struct s_rect
{
	int	x;
	int	y;
	int	w;
	int	h;
}	t_rect;

typedef struct s_hud_text
{
	int	x;
	int	y;
	int	color;
	int	scale;
}	t_hud_text;

/*
** Bonus texture banks loaded at startup.
*/
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

/*
** Retro framebuffer and minimap output state.
*/
typedef struct s_bonus_retro
{
	t_img	fb;
	t_img	out;
	t_img	minimap;
	int		enabled;
	double	minimap_zoom;
}	t_bonus_retro;

/*
** Ordered bonus level list and current level index.
*/
typedef struct s_bonus_levels
{
	const char	*paths[BONUS_LEVEL_MAX];
	const char	*start_path;
	int			count;
	int			current;
	int			active;
}	t_bonus_levels;

/*
** Player gameplay stats used by pickups and HUD.
*/
typedef struct s_bonus_stats
{
	int	hp;
	int	armor;
	int	ammo;
	int	score;
}	t_bonus_stats;

/*
** HUD textures and animation state.
*/
typedef struct s_bonus_hud
{
	t_img	face_straight[5][3];
	t_img	face_left[5];
	t_img	face_right[5];
	t_img	face_ouch[5];
	t_img	face_kill[5];
	t_img	face_dead;
	t_img	weapon_idle;
	t_img	weapon_shoot[BONUS_WEAPON_SHOOT_FRAMES];
	int		weapon_frame;
	double	weapon_timer;
	double	weapon_cooldown;
	int		face_react;
	double	face_react_timer;
	double	face_idle_timer;
	int		face_idle_frame;
	int		face_turn_dir;
	double	face_prev_angle;
}	t_bonus_hud;

/*
** Pickups are persistent map entities, separate from render sprites.
*/
typedef struct s_pickup
{
	double	x;
	double	y;
	char	type;
	char	collected;
}	t_pickup;

typedef struct s_bonus_pickups
{
	t_pickup	*items;
	int			count;
	int			cap;
}	t_bonus_pickups;

/*
** Renderable sprite data and depth buffer.
*/
typedef struct s_bonus_sprites
{
	t_img	pickup_frames[BONUS_PICKUP_FRAMES];
	t_img	pickup_hp;
	t_img	pickup_ammo;
	t_img	pickup_armor;
	double	*xs;
	double	*ys;
	char	*types;
	char	*active;
	double	*dists;
	int		count;
	int		cap;
	double	*zbuf;
	int		zcap;
	int		anim_frame;
	double	anim_timer;
}	t_bonus_sprites;

/*
** Per-sprite projection calculated for one frame.
*/
typedef struct s_sprite_proj
{
	int		sx;
	int		sw;
	int		sh;
	int		x0;
	int		x1;
	int		y0;
	int		y1;
	int		tx0;
	int		tx1;
	int		ty0;
	int		ty1;
	double	sy;
}	t_sprite_proj;

/*
** Single bonus namespace embedded in t_app.
** Mandatory builds keep this struct in t_app but link no-op bonus functions,
** so these fields stay inactive unless the bonus target is built.
*/
typedef struct s_bonus_ctx
{
	t_bonus_assets	assets;
	t_bonus_retro	retro;
	t_bonus_doors	doors;
	t_bonus_levels	levels;
	t_bonus_pickups	pickups;
	t_bonus_sprites	sprites;
	t_bonus_stats	stats;
	t_bonus_hud		hud;
}	t_bonus_ctx;

#endif
