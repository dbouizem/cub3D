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

int				retro_init(t_app *app);
int				retro_begin(t_app *app, t_img *saved_frame);
int				retro_render(t_app *app, t_img *saved_frame);
void			retro_shutdown(t_app *app);

int				retro_init_img(t_app *app, t_img *img, int width, int height);
void			retro_reset_img(t_img *img);
void			retro_destroy_img(t_app *app, t_img *img);
unsigned int	retro_get_pixel(t_img *img, int x, int y);
void			retro_upscale_to_out(t_app *app);

#endif
