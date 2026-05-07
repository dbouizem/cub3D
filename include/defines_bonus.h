/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 10:25:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/05/07 10:27:27 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_BONUS_H
# define DEFINES_BONUS_H

/*
** Table of contents:
**   1. Render & level
**   2. Player input & doors
**   3. Minimap
**   4. Shading & gamma
**   5. Alphabets & lookup sizes
**   6. Animated walls  (constants + XPM paths together)
**   7. Wall textures   (static)
**   8. Door textures
**   9. Sprite & pickup
**  10. Weapon & HUD
*/

/* ---- 1. RENDER & LEVEL -------------------------------------------------- */

# define BONUS_RENDER_W	640
# define BONUS_RENDER_H	360
# define BONUS_LEVEL_MAX	8
# define BONUS_WARN_FB_INIT	"Warning\nBonus disabled: fb init failed\n"
# define BONUS_WARN_OUT_INIT	"Warning\nBonus disabled: out init failed\n"

/* ---- 2. PLAYER INPUT & DOORS -------------------------------------------- */

# define BONUS_MOUSE_SENS	0.0025
# define BONUS_DOOR_INTERACT_COOLDOWN	0.2
# define BONUS_DOOR_INTERACT_DIST	1.20
# define BONUS_DOOR_SCAN_STEP	0.08
# define BONUS_DOOR_SPEED	1.80
# define BONUS_DOOR_PASSABLE	0.90

/* ---- 3. MINIMAP ---------------------------------------------------------- */

/*
** Layout
*/
# define BONUS_MINIMAP_TILE	7
# define BONUS_MINIMAP_RADIUS	10
# define BONUS_MINIMAP_PAD	8
# define BONUS_MINIMAP_RING_THICKNESS	3

/*
** Zoom
*/
# define BONUS_MINIMAP_ZOOM_DEFAULT	1.35
# define BONUS_MINIMAP_ZOOM_MIN	0.75
# define BONUS_MINIMAP_ZOOM_MAX	2.75
# define BONUS_MINIMAP_ZOOM_STEP	0.15

/*
** Color palette
*/
# define BONUS_MINIMAP_BG	0x00151820
# define BONUS_MINIMAP_VOID	0x0020303A
# define BONUS_MINIMAP_FLOOR	0x00405060
# define BONUS_MINIMAP_WALL	0x00D7D7D7
# define BONUS_MINIMAP_DOOR_C	0x00D39C52
# define BONUS_MINIMAP_DOOR_O	0x003FA36B
# define BONUS_MINIMAP_PLAYER	0x00FF4D4D
# define BONUS_MINIMAP_DIR	0x00FFE37A
# define BONUS_MINIMAP_RING	0x00FFFFFF
# define BONUS_MINIMAP_RING_INNER	0x00B8C7D1
# define BONUS_MINIMAP_SHADOW	0x00060A0D

/* ---- 4. SHADING & GAMMA ------------------------------------------------- */

# define BONUS_SHADE_DIST	0.10
# define BONUS_SHADE_MIN	0.75
# define BONUS_SHADE_SIDE	0.97
# define BONUS_SHADE_GAMMA	1.00
# define BONUS_SHADE_LEVELS	0
# define BONUS_SHADE_AMBIENT	0.10
# define BONUS_PALETTE_STEPS	0

# define BONUS_FACE_E	1.00
# define BONUS_FACE_W	0.98
# define BONUS_FACE_N	0.99
# define BONUS_FACE_S	0.97

# define BONUS_FLAT_HORIZON	0.96
# define BONUS_FLAT_CEIL_TOP	1.02
# define BONUS_FLAT_FLOOR_BOTTOM	0.92
# define BONUS_FLAT_GAMMA	1.00

# define BONUS_VIGNETTE_STRENGTH	0.06
# define BONUS_VIGNETTE_POWER	1.80

/* ---- 5. ALPHABETS & LOOKUP SIZES ---------------------------------------- */

# define BONUS_WALL_COUNT	34
# define BONUS_WALL_SYMBOL_COUNT	32
# define BONUS_DOOR_COUNT	2

# define BONUS_DOOR_SET	"AD"
# define BONUS_PLAYER_SET	"NSEW"
# define BONUS_WALL_SYMBOL_SET	"!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"
# define BONUS_SPRITE_SET	"*@)/"

/* ---- 6. ANIMATED WALLS  (frames, fps, and XPM paths) -------------------- */

/*
** Tile O  — level 2 animated area
*/
# define BONUS_ANIM_O_FRAMES	3
# define BONUS_ANIM_O_FPS	6.0
# define BONUS_WALL_O1_XPM	"textures/bonus/walls/wall_a/wall_a23.xpm"
# define BONUS_WALL_O2_XPM	"textures/bonus/walls/wall_a/wall_a24.xpm"
# define BONUS_WALL_O3_XPM	"textures/bonus/walls/wall_a/wall_a25.xpm"
# define BONUS_WALL_O_XPM	BONUS_WALL_O1_XPM

/*
** Tile P  — level 7 flesh
*/
# define BONUS_ANIM_P_FRAMES	3
# define BONUS_ANIM_P_FPS	3.0
# define BONUS_WALL_P1_XPM	"textures/bonus/walls/wall_f/wall_fa21.xpm"
# define BONUS_WALL_P2_XPM	"textures/bonus/walls/wall_f/wall_fa22.xpm"
# define BONUS_WALL_P3_XPM	"textures/bonus/walls/wall_f/wall_fa23.xpm"
# define BONUS_WALL_P_XPM	BONUS_WALL_P1_XPM

/*
** Tile Q  — level 6 marble
*/
# define BONUS_ANIM_Q_FRAMES	3
# define BONUS_ANIM_Q_FPS	6.0
# define BONUS_WALL_Q1_XPM	"textures/bonus/walls/wall_m/wall_ma21.xpm"
# define BONUS_WALL_Q2_XPM	"textures/bonus/walls/wall_m/wall_ma22.xpm"
# define BONUS_WALL_Q3_XPM	"textures/bonus/walls/wall_m/wall_ma23.xpm"
# define BONUS_WALL_Q_XPM	BONUS_WALL_Q1_XPM

/*
** Tile *  — animated star (wall_p)
*/
# define BONUS_ANIM_STAR_FRAMES	4
# define BONUS_ANIM_STAR_FPS	3.0
# define BONUS_WALL_STAR1_XPM	"textures/bonus/walls/wall_p/wall_pa1.xpm"
# define BONUS_WALL_STAR2_XPM	"textures/bonus/walls/wall_p/wall_pa2.xpm"
# define BONUS_WALL_STAR3_XPM	"textures/bonus/walls/wall_p/wall_pa3.xpm"
# define BONUS_WALL_STAR4_XPM	"textures/bonus/walls/wall_p/wall_pa4.xpm"
# define BONUS_WALL_STAR_XPM	BONUS_WALL_STAR1_XPM

/*
** Tile .  — animated dot (wall_c)
*/
# define BONUS_ANIM_DOT_FRAMES	4
# define BONUS_ANIM_DOT_FPS	9.0
# define BONUS_WALL_DOT1_XPM	"textures/bonus/walls/wall_c/wall_ca1.xpm"
# define BONUS_WALL_DOT2_XPM	"textures/bonus/walls/wall_c/wall_ca2.xpm"
# define BONUS_WALL_DOT3_XPM	"textures/bonus/walls/wall_c/wall_ca3.xpm"
# define BONUS_WALL_DOT4_XPM	"textures/bonus/walls/wall_c/wall_ca4.xpm"
# define BONUS_WALL_DOT_XPM	BONUS_WALL_DOT1_XPM

/*
** Tile (  — animated lparen (wall_f)
*/
# define BONUS_ANIM_LPAREN_FRAMES	4
# define BONUS_ANIM_LPAREN_FPS	3.0
# define BONUS_WALL_LPAREN1_XPM	"textures/bonus/walls/wall_f/wall_fa1.xpm"
# define BONUS_WALL_LPAREN2_XPM	"textures/bonus/walls/wall_f/wall_fa2.xpm"
# define BONUS_WALL_LPAREN3_XPM	"textures/bonus/walls/wall_f/wall_fa3.xpm"
# define BONUS_WALL_LPAREN4_XPM	"textures/bonus/walls/wall_f/wall_fa4.xpm"
# define BONUS_WALL_LPAREN_XPM	BONUS_WALL_LPAREN1_XPM

/* ---- 7. WALL TEXTURES  (static) ----------------------------------------- */

# define BONUS_WALL_DEFAULT_XPM	"textures/bonus/walls/wall_s/wall_s.xpm"

/*
** Level 1 — stone set  (tiles 2–7)
*/
# define BONUS_WALL2_XPM	"textures/bonus/walls/wall_s/wall_s.xpm"
# define BONUS_WALL3_XPM	"textures/bonus/walls/wall_s/wall_s1.xpm"
# define BONUS_WALL4_XPM	"textures/bonus/walls/wall_s/wall_s2.xpm"
# define BONUS_WALL5_XPM	"textures/bonus/walls/wall_s/wall_s3.xpm"
# define BONUS_WALL6_XPM	"textures/bonus/walls/wall_s/wall_s4.xpm"
# define BONUS_WALL7_XPM	"textures/bonus/walls/wall_s/wall_s5.xpm"

/*
** Level 2 — animated area set  (tiles g–n, o is in section 6)
*/
# define BONUS_WALL_G_XPM	"textures/bonus/walls/wall_a/wall_a12.xpm"
# define BONUS_WALL_H_XPM	"textures/bonus/walls/wall_a/wall_a11.xpm"
# define BONUS_WALL_I_XPM	"textures/bonus/walls/wall_a/wall_a33.xpm"
# define BONUS_WALL_J_XPM	"textures/bonus/walls/wall_a/wall_a32.xpm"
# define BONUS_WALL_K_XPM	"textures/bonus/walls/wall_a/wall_a41.xpm"
# define BONUS_WALL_L_XPM	"textures/bonus/walls/wall_a/wall_a42.xpm"
# define BONUS_WALL_M_XPM	"textures/bonus/walls/wall_a/wall_a21.xpm"
# define BONUS_WALL_N_XPM	"textures/bonus/walls/wall_a/wall_a22.xpm"

/*
** Level 3 — gray set  (symbol tiles !, ", #, $, %, &)
*/
# define BONUS_WALL_EXCL_XPM	"textures/bonus/walls/wall_g/wall_g1.xpm"
# define BONUS_WALL_DQUOTE_XPM	"textures/bonus/walls/wall_g/wall_g2.xpm"
# define BONUS_WALL_HASH_XPM	"textures/bonus/walls/wall_g/wall_g3.xpm"
# define BONUS_WALL_DOLLAR_XPM	"textures/bonus/walls/wall_g/wall_g4.xpm"
# define BONUS_WALL_PERCENT_XPM	"textures/bonus/walls/wall_g/wall_g5.xpm"
# define BONUS_WALL_AMP_XPM	"textures/bonus/walls/wall_g/wall_g6.xpm"

/*
** Level 4 — tech set  (tiles d, e, f)
*/
# define BONUS_WALL_D_XPM	"textures/bonus/walls/wall_t/wall_t.xpm"
# define BONUS_WALL_E_XPM	"textures/bonus/walls/wall_t/wall_t1.xpm"
# define BONUS_WALL_F_XPM	"textures/bonus/walls/wall_t/wall_t2.xpm"

/*
** Level 5 — computer set  (tiles +, comma, -, . is animated in section 6)
*/
# define BONUS_WALL_PLUS_XPM	"textures/bonus/walls/wall_c/wall_c1.xpm"
# define BONUS_WALL_COMMA_XPM	"textures/bonus/walls/wall_c/wall_c2.xpm"
# define BONUS_WALL_MINUS_XPM	"textures/bonus/walls/wall_c/wall_c3.xpm"

/*
** Level 6 — marble set  (tiles r–z, q is animated in section 6)
*/
# define BONUS_WALL_R_XPM	"textures/bonus/walls/wall_m/wall_m10.xpm"
# define BONUS_WALL_S_XPM	"textures/bonus/walls/wall_m/wall_m26.xpm"
# define BONUS_WALL_T_XPM	"textures/bonus/walls/wall_m/wall_m13.xpm"
# define BONUS_WALL_U_XPM	"textures/bonus/walls/wall_m/wall_m14.xpm"
# define BONUS_WALL_V_XPM	"textures/bonus/walls/wall_m/wall_m15.xpm"
# define BONUS_WALL_W_XPM	"textures/bonus/walls/wall_m/wall_m25.xpm"
# define BONUS_WALL_X_XPM	"textures/bonus/walls/wall_m/wall_m20.xpm"
# define BONUS_WALL_Y_XPM	"textures/bonus/walls/wall_m/wall_m21.xpm"
# define BONUS_WALL_Z_XPM	"textures/bonus/walls/wall_m/wall_m24.xpm"

/*
** Level 7 — flesh set  (tile ', p is animated in section 6, ( is animated)
*/
# define BONUS_WALL_SQUOTE_XPM	"textures/bonus/walls/wall_f/wall_f1.xpm"

/*
** Level 8 — exit set  (tiles 8, 9, a, b, c)
*/
# define BONUS_WALL8_XPM	"textures/bonus/walls/wall_e/wall_e.xpm"
# define BONUS_WALL9_XPM	"textures/bonus/walls/wall_e/wall_e1.xpm"
# define BONUS_WALL_A_XPM	"textures/bonus/walls/wall_e/wall_e2.xpm"
# define BONUS_WALL_B_XPM	"textures/bonus/walls/wall_e/wall_e3.xpm"
# define BONUS_WALL_C_XPM	"textures/bonus/walls/wall_e/wall_e4.xpm"

/*
** Fallbacks — not yet textured  (symbol tiles without dedicated art)
*/
# define BONUS_WALL_RPAREN_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_SLASH_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_COLON_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_SEMI_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_LT_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_EQ_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_GT_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_QMARK_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_AT_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_LBRACK_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_BSLASH_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_RBRACK_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_CARET_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_UNDERSCORE_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_BACKTICK_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_LBRACE_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_PIPE_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_RBRACE_XPM	BONUS_WALL_DEFAULT_XPM
# define BONUS_WALL_TILDE_XPM	BONUS_WALL_DEFAULT_XPM

/* ---- 8. DOOR TEXTURES --------------------------------------------------- */

# define BONUS_DOOR_DEFAULT_XPM	"textures/bonus/doors/door_s.xpm"
# define BONUS_DOOR_A_XPM	"textures/bonus/doors/door_a.xpm"

/*
** Fallbacks — not yet textured
*/
# define BONUS_DOOR_B_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_C_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_D_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_F_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_G_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_H_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_I_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_J_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_K_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_L_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_M_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_O_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_P_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_Q_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_R_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_T_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_U_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_V_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_X_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_Y_XPM	BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_Z_XPM	BONUS_DOOR_DEFAULT_XPM

/* ---- 9. SPRITE & PICKUP ------------------------------------------------- */

/*
** Pickup animation frames
*/
# define BONUS_PICKUP_FRAMES	4
# define BONUS_PICKUP_FRAME_TIME	0.12
# define BONUS_PICKUP_FRAME_1_XPM	"textures/bonus/pickups/bon1a0.xpm"
# define BONUS_PICKUP_FRAME_2_XPM	"textures/bonus/pickups/bon1b0.xpm"
# define BONUS_PICKUP_FRAME_3_XPM	"textures/bonus/pickups/bon1c0.xpm"
# define BONUS_PICKUP_FRAME_4_XPM	"textures/bonus/pickups/bon1d0.xpm"

/*
** Pickup item textures
*/
# define BONUS_PICKUP_HP_XPM	"textures/bonus/pickups/media0.xpm"
# define BONUS_PICKUP_AMMO_XPM	"textures/bonus/pickups/shela0.xpm"
# define BONUS_PICKUP_ARMOR_XPM	"textures/bonus/pickups/arm1a0.xpm"

/*
** Sprite rendering
*/
# define BONUS_PICKUP_RADIUS	0.42
# define BONUS_SPRITE_FLOOR_OFFSET	1.48
# define BONUS_SPRITE_SHADOW_W	0.88
# define BONUS_SPRITE_SHADOW_H	0.16
# define BONUS_SPRITE_SHADOW_DARKEN	0.42
# define BONUS_PICKUP_AMMO_SCALE	0.75
# define BONUS_PICKUP_ARMOR_SCALE	0.90
# define BONUS_PICKUP_SCORE_SCALE	0.72
# define BONUS_SPRITE_SCALE	0.22

/*
** Player stats & pickup gains
*/
# define BONUS_HP_START	100
# define BONUS_HP_MAX	100
# define BONUS_ARMOR_START	0
# define BONUS_ARMOR_MAX	200
# define BONUS_AMMO_START	24
# define BONUS_AMMO_MAX	99
# define BONUS_SCORE_START	0
# define BONUS_SCORE_MAX	9999
# define BONUS_PICKUP_HP_GAIN	25
# define BONUS_PICKUP_ARMOR_GAIN	25
# define BONUS_PICKUP_AMMO_GAIN	12
# define BONUS_PICKUP_SCORE_GAIN	100

/* ---- 10. WEAPON & HUD --------------------------------------------------- */

/*
** Pistol animation frames
*/
# define BONUS_WEAPON_SHOOT_FRAMES	3
# define BONUS_WEAPON_IDLE_1_XPM	\
	"textures/bonus/weapons/pistol/weapon_idle_1.xpm"
# define BONUS_WEAPON_SHOOT_1_XPM	\
	"textures/bonus/weapons/pistol/weapon_shoot_1.xpm"
# define BONUS_WEAPON_SHOOT_2_XPM	\
	"textures/bonus/weapons/pistol/weapon_shoot_2.xpm"
# define BONUS_WEAPON_SHOOT_3_XPM	\
	"textures/bonus/weapons/pistol/weapon_shoot_3.xpm"

/*
** Weapon timing & hitscan
*/
# define BONUS_WEAPON_FIRE_COOLDOWN	0.30
# define BONUS_WEAPON_FRAME_TIME	0.05
# define BONUS_WEAPON_RANGE	8.0
# define BONUS_WEAPON_STEP	0.08
# define BONUS_WEAPON_HIT_RADIUS	0.20

/*
** HUD face & bar
*/
# define BONUS_HUD_FACE_XPM	"textures/bonus/player/stfst00.xpm"
# define BONUS_HUD_BAR_H	96
# define BONUS_HUD_FACE_REACT_TIME	0.28
# define BONUS_HUD_FACE_IDLE_TIME	0.28
# define BONUS_HUD_FACE_TURN_EPS	0.08

#endif
