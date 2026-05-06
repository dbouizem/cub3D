/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 10:25:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/06 10:25:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "structs.h"

typedef struct s_app	t_app;
typedef struct s_ray	t_ray;
typedef struct s_player	t_player;

/*
** Retro framebuffer, minimap, and shading.
*/
int				retro_init(t_app *app);
int				retro_begin(t_app *app, t_img *saved_frame);
int				retro_render(t_app *app, t_img *saved_frame);
void			retro_shutdown(t_app *app);
int				bonus_apply_resolution_preset(t_app *app, int keycode);
int				retro_init_img(t_app *app, t_img *img, int width, int height);
void			retro_reset_img(t_img *img);
void			retro_destroy_img(t_app *app, t_img *img);
unsigned int	retro_get_pixel(t_img *img, int x, int y);
void			retro_upscale_to_out(t_app *app);
int				apply_wall_shading(int color, t_ray ray);
int				apply_flat_shading(int color, int y, int height);
void			bonus_draw_minimap(t_app *app);
void			bonus_minimap_clear(t_img *img);
void			bonus_minimap_render_pixels(t_app *app, t_img *img, t_mm mm);
void			bonus_minimap_draw_player(t_img *img, t_mm mm);
void			bonus_minimap_blit(t_app *app, t_img *img, t_mm mm);

/*
** Bonus wall and door texture banks.
*/
int				bonus_is_valid_map_char(char c);
int				bonus_is_solid_tile(char c);
int				bonus_load_wall_textures(t_app *app);
void			bonus_init_wall_path_tables(const char **wall_paths,
					const char **door_paths);
int				bonus_load_wall_anim_textures(t_app *app);
void			bonus_destroy_wall_textures(t_app *app);
t_img			*bonus_pick_wall_texture(t_app *app, char tile);
int				bonus_symbol_index(char c);
t_img			*bonus_pick_symbol_texture(t_app *app, char tile);
t_img			*bonus_pick_door_texture(t_app *app, char tile);
t_img			*bonus_pick_anim_texture(t_app *app, char tile);
int				bonus_load_symbol_textures(t_app *app);
void			bonus_destroy_symbol_textures(t_app *app);

/*
** Door gameplay state.
*/
int				bonus_doors_init(t_app *app);
void			bonus_doors_update(t_app *app);
void			bonus_doors_shutdown(t_app *app);
int				bonus_door_try_toggle(t_app *app);
int				bonus_door_is_open_at(t_app *app, int x, int y);
int				bonus_door_is_blocking(t_app *app, double px, double py);
int				bonus_door_blocks_axis(t_app *app, double px, double py,
					int axis);
double			bonus_door_open_progress_at(t_app *app, int x, int y);
int				bonus_door_allows_passage_at(t_app *app, int x, int y,
					double hit);
int				bonus_door_state_at(t_app *app, int x, int y);
int				bonus_is_door_tile(char c);
char			bonus_map_cell_at(t_app *app, int x, int y);
t_door			*bonus_find_door(t_app *app, int x, int y);
int				bonus_find_front_door(t_app *app, int *x, int *y);
int				bonus_door_is_occupied(t_app *app, t_door *door);
void			bonus_toggle_door_state(t_app *app, t_door *door);

/*
** Bonus level sequence and reload.
*/
int				bonus_levels_init(t_app *app, const char *start_path);
const char		*bonus_level_current_path(t_app *app);
int				bonus_load_next_level(t_app *app);
void			bonus_destroy_level_tex(t_app *app, t_img *img);
int				bonus_load_next_level_textures(t_app *app, t_app *next,
					t_img tex[4]);
void			bonus_transfer_next_level(t_app *app, t_app *next,
					t_img tex[4]);

/*
** HUD and weapon overlay.
*/
int				bonus_hud_init(t_app *app);
void			bonus_hud_shutdown(t_app *app);
void			bonus_hud_update(t_app *app);
void			bonus_draw_hud(t_app *app);
int				bonus_hud_try_fire(t_app *app);
void			bonus_hud_reset_state(t_app *app);
void			bonus_fill_rect(t_img *img, t_rect r, int color);
void			bonus_draw_digit(t_img *img, t_hud_text txt, int digit);
void			bonus_draw_label_glyph(t_img *img, t_hud_text txt, char c);
int				bonus_label_width(const char *text, int scale);
int				bonus_number_width(int digits, int scale);
void			bonus_draw_label(t_img *img, t_hud_text txt, const char *text);
void			bonus_draw_number(t_img *img, t_hud_text txt, int val,
					int digits);
void			bonus_find_visible_hud_bounds(t_img *img, int bounds[4]);
void			bonus_blit_masked_bounds(t_img *dst, t_img *src, t_rect r,
					int bounds[4]);
void			bonus_blit_scaled(t_img *dst, t_img *src, t_rect r);
t_img			*bonus_face_current_frame(t_app *app);
t_img			*bonus_weapon_current_frame(t_app *app);
void			bonus_draw_panel_frame(t_img *img, t_rect r);
void			bonus_draw_hud_backplate(t_img *img, int y, int h);
void			bonus_draw_hud_texture(t_img *img, t_rect r);
void			bonus_draw_rivet(t_img *img, int x, int y);
void			bonus_draw_mid_stat_box(t_img *img, t_rect r,
					const char *label);
void			bonus_draw_big_stat(t_img *img, int x, int y, int value);
void			bonus_draw_face_panel(t_app *app, t_img *img, t_rect r);
void			bonus_draw_level_box(t_app *app, t_img *img, t_rect r);
void			bonus_draw_left_hud(t_app *app, t_img *img, int bar_y,
					int face_x);
void			bonus_draw_weapon_slot(t_img *img, t_rect r);
void			bonus_draw_status_bar(t_app *app, t_img *img);
void			bonus_draw_weapon_overlay(t_app *app, t_img *dst, t_img *src);
const char		*bonus_face_straight_path(int i, int j);
const char		*bonus_face_left_path(int i);
const char		*bonus_face_right_path(int i);
const char		*bonus_face_ouch_path(int i);
const char		*bonus_face_kill_path(int i);

/*
** Pickups and sprite rendering.
*/
int				bonus_pickups_rebuild(t_app *app);
void			bonus_pickups_shutdown(t_app *app);
int				bonus_pickup_collect(t_app *app, t_pickup *pickup);
void			bonus_apply_damage(t_app *app, int damage);
void			bonus_pickups_update(t_app *app);
int				bonus_pickups_count_active(t_app *app);
void			bonus_pickups_fill_active_sprites(t_app *app);
int				bonus_sprites_init(t_app *app);
void			bonus_sprites_shutdown(t_app *app);
int				bonus_sprites_rebuild(t_app *app);
int				bonus_sprites_resize_zbuf(t_app *app, int width);
void			bonus_sprites_set_depth(t_app *app, int x, double dist);
void			bonus_draw_sprites(t_app *app);
int				bonus_sprite_is_opaque(unsigned int color);
void			bonus_sprite_setup_bounds(t_img *tex, t_sprite_proj *p);
int				bonus_setup_sprite_projection(t_app *app, int i,
					t_sprite_proj *p, t_img **tex);
void			bonus_draw_sprite_shadow(t_app *app, t_sprite_proj p);
int				bonus_is_sprite_tile(char c);
void			sort_bonus_sprites(t_bonus_sprites *sp);
void			bonus_sprite_destroy_tex(t_app *app, t_img *img);
char			*bonus_resolve_asset_path(t_app *app, const char *path);
int				bonus_sprite_load_tex(t_app *app, t_img *img, const char *path);
int				bonus_sprite_ensure_cap(t_bonus_sprites *sp, int cap);
t_img			*bonus_pick_sprite_texture(t_app *app, char type);
void			bonus_shift_sprite_space(t_bonus_sprites *sp,
					t_player *pl, double sign);

#endif
