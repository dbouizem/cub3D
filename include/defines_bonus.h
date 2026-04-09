/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 10:25:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 12:29:16 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_BONUS_H
# define DEFINES_BONUS_H

# define BONUS_RENDER_W 640
# define BONUS_RENDER_H 360

# define BONUS_WARN_FB_INIT "Warning\nBonus disabled: fb init failed\n"
# define BONUS_WARN_OUT_INIT "Warning\nBonus disabled: out init failed\n"
# define BONUS_MOUSE_SENS 0.0025
# define BONUS_DOOR_INTERACT_COOLDOWN 0.2
# define BONUS_DOOR_INTERACT_DIST 1.20
# define BONUS_DOOR_SCAN_STEP 0.08
# define BONUS_DOOR_SPEED 1.80
# define BONUS_DOOR_PASSABLE 0.90

# define BONUS_SHADE_DIST 0.14
# define BONUS_SHADE_MIN 0.45
# define BONUS_SHADE_SIDE 0.95
# define BONUS_SHADE_GAMMA 0.75
# define BONUS_SHADE_LEVELS 20
# define BONUS_SHADE_AMBIENT 0.25
# define BONUS_PALETTE_STEPS 24
# define BONUS_FACE_E 1.00
# define BONUS_FACE_W 0.97
# define BONUS_FACE_N 0.99
# define BONUS_FACE_S 0.95
# define BONUS_FLAT_HORIZON 0.78
# define BONUS_FLAT_CEIL_TOP 1.00
# define BONUS_FLAT_FLOOR_BOTTOM 1.00
# define BONUS_FLAT_GAMMA 0.90
# define BONUS_ANIM_O_FRAMES 3
# define BONUS_ANIM_O_FPS 6.0
# define BONUS_ANIM_P_FRAMES 3
# define BONUS_ANIM_P_FPS 3.0
# define BONUS_ANIM_Q_FRAMES 3
# define BONUS_ANIM_Q_FPS 6.0
# define BONUS_ANIM_STAR_FRAMES 4
# define BONUS_ANIM_STAR_FPS 3.0
# define BONUS_ANIM_DOT_FRAMES 4
# define BONUS_ANIM_DOT_FPS 9.0
# define BONUS_ANIM_LPAREN_FRAMES 4
# define BONUS_ANIM_LPAREN_FPS 3.0

# define BONUS_WALL_COUNT 34
# define BONUS_WALL_SYMBOL_COUNT 32
# define BONUS_DOOR_COUNT 22

# define BONUS_DOOR_SET "ABCDFGHIJKLMOPQRTUVXYZ"
# define BONUS_WALL_SYMBOL_SET "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"

# define BONUS_WALL_DEFAULT_XPM "textures/bonus/walls/wall_s/wall_s.xpm"

// ----- WALLS -----

// MAP LEVEL1
# define BONUS_WALL2_XPM "textures/bonus/walls/wall_s/wall_s.xpm"
# define BONUS_WALL3_XPM "textures/bonus/walls/wall_s/wall_s1.xpm"
# define BONUS_WALL4_XPM "textures/bonus/walls/wall_s/wall_s2.xpm"
# define BONUS_WALL5_XPM "textures/bonus/walls/wall_s/wall_s3.xpm"
# define BONUS_WALL6_XPM "textures/bonus/walls/wall_s/wall_s4.xpm"
# define BONUS_WALL7_XPM "textures/bonus/walls/wall_s/wall_s5.xpm"

// MAP LEVEL8
# define BONUS_WALL8_XPM "textures/bonus/walls/wall_e/wall_e.xpm"
# define BONUS_WALL9_XPM "textures/bonus/walls/wall_e/wall_e1.xpm"
# define BONUS_WALL_A_XPM "textures/bonus/walls/wall_e/wall_e2.xpm"
# define BONUS_WALL_B_XPM "textures/bonus/walls/wall_e/wall_e3.xpm"
# define BONUS_WALL_C_XPM "textures/bonus/walls/wall_e/wall_e4.xpm"

// MAP LEVEL4
# define BONUS_WALL_D_XPM "textures/bonus/walls/wall_t/wall_t.xpm"
# define BONUS_WALL_E_XPM "textures/bonus/walls/wall_t/wall_t1.xpm"
# define BONUS_WALL_F_XPM "textures/bonus/walls/wall_t/wall_t2.xpm"

// MAP LEVEL2
# define BONUS_WALL_G_XPM "textures/bonus/walls/wall_a/wall_a12.xpm"
# define BONUS_WALL_H_XPM "textures/bonus/walls/wall_a/wall_a11.xpm"
# define BONUS_WALL_I_XPM "textures/bonus/walls/wall_a/wall_a33.xpm"
# define BONUS_WALL_J_XPM "textures/bonus/walls/wall_a/wall_a32.xpm"
# define BONUS_WALL_K_XPM "textures/bonus/walls/wall_a/wall_a41.xpm"
# define BONUS_WALL_L_XPM "textures/bonus/walls/wall_a/wall_a42.xpm"
# define BONUS_WALL_M_XPM "textures/bonus/walls/wall_a/wall_a21.xpm"
# define BONUS_WALL_N_XPM "textures/bonus/walls/wall_a/wall_a22.xpm"
# define BONUS_WALL_O1_XPM "textures/bonus/walls/wall_a/wall_a23.xpm"
# define BONUS_WALL_O2_XPM "textures/bonus/walls/wall_a/wall_a24.xpm"
# define BONUS_WALL_O3_XPM "textures/bonus/walls/wall_a/wall_a25.xpm"
# define BONUS_WALL_O_XPM BONUS_WALL_O1_XPM

// MAP LEVEL6

# define BONUS_WALL_Q1_XPM "textures/bonus/walls/wall_m/wall_ma21.xpm"
# define BONUS_WALL_Q2_XPM "textures/bonus/walls/wall_m/wall_ma22.xpm"
# define BONUS_WALL_Q3_XPM "textures/bonus/walls/wall_m/wall_ma23.xpm"
# define BONUS_WALL_Q_XPM BONUS_WALL_Q1_XPM
# define BONUS_WALL_R_XPM "textures/bonus/walls/wall_m/wall_m10.xpm"
# define BONUS_WALL_S_XPM "textures/bonus/walls/wall_m/wall_m26.xpm"
# define BONUS_WALL_T_XPM "textures/bonus/walls/wall_m/wall_m13.xpm"
# define BONUS_WALL_U_XPM "textures/bonus/walls/wall_m/wall_m14.xpm"
# define BONUS_WALL_V_XPM "textures/bonus/walls/wall_m/wall_m15.xpm"
# define BONUS_WALL_W_XPM "textures/bonus/walls/wall_m/wall_m25.xpm"
# define BONUS_WALL_X_XPM "textures/bonus/walls/wall_m/wall_m20.xpm"
# define BONUS_WALL_Y_XPM "textures/bonus/walls/wall_m/wall_m21.xpm"
# define BONUS_WALL_Z_XPM "textures/bonus/walls/wall_m/wall_m24.xpm"

// MAP LEVEL3
# define BONUS_WALL_EXCL_XPM "textures/bonus/walls/wall_g/wall_g1.xpm" // !
# define BONUS_WALL_DQUOTE_XPM 	"textures/bonus/walls/wall_g/wall_g2.xpm"// "
# define BONUS_WALL_HASH_XPM "textures/bonus/walls/wall_g/wall_g3.xpm" // #
# define BONUS_WALL_DOLLAR_XPM "textures/bonus/walls/wall_g/wall_g4.xpm" // $
# define BONUS_WALL_PERCENT_XPM "textures/bonus/walls/wall_g/wall_g5.xpm" // %
# define BONUS_WALL_AMP_XPM "textures/bonus/walls/wall_g/wall_g6.xpm" // &

// MAP LEVEL7
# define BONUS_WALL_P1_XPM "textures/bonus/walls/wall_f/wall_fa21.xpm"
# define BONUS_WALL_P2_XPM "textures/bonus/walls/wall_f/wall_fa22.xpm"
# define BONUS_WALL_P3_XPM "textures/bonus/walls/wall_f/wall_fa23.xpm"
# define BONUS_WALL_P_XPM BONUS_WALL_P1_XPM
# define BONUS_WALL_SQUOTE_XPM "textures/bonus/walls/wall_f/wall_f1.xpm" // '
# define BONUS_WALL_LPAREN1_XPM "textures/bonus/walls/wall_f/wall_fa1.xpm"
# define BONUS_WALL_LPAREN2_XPM "textures/bonus/walls/wall_f/wall_fa2.xpm"
# define BONUS_WALL_LPAREN3_XPM "textures/bonus/walls/wall_f/wall_fa3.xpm"
# define BONUS_WALL_LPAREN4_XPM "textures/bonus/walls/wall_f/wall_fa4.xpm"
# define BONUS_WALL_LPAREN_XPM BONUS_WALL_LPAREN1_XPM // (

// MAP LEVEL5
// option 1
# define BONUS_WALL_RPAREN_XPM "textures/bonus/walls/wall_p/wall.xpm" //)
# define BONUS_WALL_STAR1_XPM "textures/bonus/walls/wall_p/wall_pa1.xpm"
# define BONUS_WALL_STAR2_XPM "textures/bonus/walls/wall_p/wall_pa2.xpm"
# define BONUS_WALL_STAR3_XPM "textures/bonus/walls/wall_p/wall_pa3.xpm"
# define BONUS_WALL_STAR4_XPM "textures/bonus/walls/wall_p/wall_pa4.xpm"
# define BONUS_WALL_STAR_XPM BONUS_WALL_STAR1_XPM // *
// option 2
# define BONUS_WALL_PLUS_XPM "textures/bonus/walls/wall_c/wall_c1.xpm" // +
# define BONUS_WALL_COMMA_XPM  "textures/bonus/walls/wall_c/wall_c2.xpm"// ,
# define BONUS_WALL_MINUS_XPM  "textures/bonus/walls/wall_c/wall_c3.xpm"// -
# define BONUS_WALL_DOT1_XPM  "textures/bonus/walls/wall_c/wall_ca1.xpm"// .
# define BONUS_WALL_DOT2_XPM  "textures/bonus/walls/wall_c/wall_ca2.xpm"// .
# define BONUS_WALL_DOT3_XPM  "textures/bonus/walls/wall_c/wall_ca3.xpm"// .
# define BONUS_WALL_DOT4_XPM  "textures/bonus/walls/wall_c/wall_ca4.xpm"// .
# define BONUS_WALL_DOT_XPM BONUS_WALL_DOT1_XPM// .

// ----- DOORS -----

# define BONUS_DOOR_DEFAULT_XPM "textures/bonus/doors/door_s.xpm"
# define BONUS_DOOR_A_XPM "textures/bonus/doors/door_a.xpm"
# define BONUS_DOOR_B_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_C_XPM BONUS_DOOR_DEFAULT_XPM

// ----- PLAYER -----

# define BONUS_DOOR_D_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_F_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_G_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_H_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_I_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_J_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_K_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_L_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_M_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_O_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_P_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_Q_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_R_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_T_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_U_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_V_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_X_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_Y_XPM BONUS_DOOR_DEFAULT_XPM
# define BONUS_DOOR_Z_XPM BONUS_DOOR_DEFAULT_XPM

// ----- SPRAYT -----

# define BONUS_WALL_SLASH_XPM BONUS_WALL_DEFAULT_XPM       // /
# define BONUS_WALL_COLON_XPM BONUS_WALL_DEFAULT_XPM       // :
# define BONUS_WALL_SEMI_XPM BONUS_WALL_DEFAULT_XPM        // ;
# define BONUS_WALL_LT_XPM BONUS_WALL_DEFAULT_XPM          // <
# define BONUS_WALL_EQ_XPM BONUS_WALL_DEFAULT_XPM          // =
# define BONUS_WALL_GT_XPM BONUS_WALL_DEFAULT_XPM          // >
# define BONUS_WALL_QMARK_XPM BONUS_WALL_DEFAULT_XPM       // ?
# define BONUS_WALL_AT_XPM BONUS_WALL_DEFAULT_XPM          // @
# define BONUS_WALL_LBRACK_XPM BONUS_WALL_DEFAULT_XPM      // [
# define BONUS_WALL_BSLASH_XPM BONUS_WALL_DEFAULT_XPM      // '\'
# define BONUS_WALL_RBRACK_XPM BONUS_WALL_DEFAULT_XPM      // ]
# define BONUS_WALL_CARET_XPM BONUS_WALL_DEFAULT_XPM       // ^
# define BONUS_WALL_UNDERSCORE_XPM BONUS_WALL_DEFAULT_XPM  // _
# define BONUS_WALL_BACKTICK_XPM BONUS_WALL_DEFAULT_XPM    // `
# define BONUS_WALL_LBRACE_XPM BONUS_WALL_DEFAULT_XPM      // {
# define BONUS_WALL_PIPE_XPM BONUS_WALL_DEFAULT_XPM        // |
# define BONUS_WALL_RBRACE_XPM BONUS_WALL_DEFAULT_XPM      // }
# define BONUS_WALL_TILDE_XPM BONUS_WALL_DEFAULT_XPM       // ~

// -----  -----

#endif
