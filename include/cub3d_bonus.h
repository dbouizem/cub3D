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

typedef struct s_app	t_app;
typedef struct s_img	t_img;
typedef struct s_ray	t_ray;
typedef struct s_door	t_door;

int				retro_init(t_app *app);
int				retro_begin(t_app *app, t_img *saved_frame);
int				retro_render(t_app *app, t_img *saved_frame);
void			retro_shutdown(t_app *app);
int				apply_wall_shading(int color, t_ray ray);
int				apply_flat_shading(int color, int y, int height);
int				bonus_is_valid_map_char(char c);
int				bonus_is_solid_tile(char c);
int				bonus_load_wall_textures(t_app *app);
void			bonus_destroy_wall_textures(t_app *app);
t_img			*bonus_pick_wall_texture(t_app *app, char tile);
int				bonus_symbol_index(char c);
t_img			*bonus_pick_symbol_texture(t_app *app, char tile);
t_img			*bonus_pick_door_texture(t_app *app, char tile);
t_img			*bonus_pick_anim_texture(t_app *app, char tile);
void			bonus_load_symbol_textures(t_app *app);
void			bonus_destroy_symbol_textures(t_app *app);
int				bonus_doors_init(t_app *app);
void			bonus_doors_update(t_app *app);
void			bonus_doors_shutdown(t_app *app);
int				bonus_door_try_toggle(t_app *app);
int				bonus_door_is_open_at(t_app *app, int x, int y);
int				bonus_door_is_blocking(t_app *app, double px, double py);
double			bonus_door_open_progress_at(t_app *app, int x, int y);
int				bonus_door_state_at(t_app *app, int x, int y);
int				bonus_is_door_tile(char c);
char			bonus_map_cell_at(t_app *app, int x, int y);
t_door			*bonus_find_door(t_app *app, int x, int y);
int				bonus_find_front_door(t_app *app, int *x, int *y);
void			bonus_toggle_door_state(t_door *door);

int				retro_init_img(t_app *app, t_img *img, int width, int height);
void			retro_reset_img(t_img *img);
void			retro_destroy_img(t_app *app, t_img *img);
unsigned int	retro_get_pixel(t_img *img, int x, int y);
void			retro_upscale_to_out(t_app *app);

#endif
