/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/10 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bonus_sprite_destroy_tex(t_app *app, t_img *img)
{
	if (app->mlx_ptr && img->img_ptr)
		mlx_destroy_image(app->mlx_ptr, img->img_ptr);
	img->img_ptr = NULL;
	img->addr = NULL;
}

int	bonus_sprite_load_tex(t_app *app, t_img *img, const char *path)
{
	img->img_ptr = mlx_xpm_file_to_image(app->mlx_ptr, (char *)path,
			&img->width, &img->height);
	if (!img->img_ptr)
		return (1);
	img->addr = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
		return (bonus_sprite_destroy_tex(app, img), 1);
	return (0);
}

int	bonus_sprite_ensure_cap(t_bonus_sprites *sp, int cap)
{
	if (cap <= sp->cap)
		return (0);
	free(sp->xs);
	free(sp->ys);
	free(sp->types);
	free(sp->dists);
	sp->xs = malloc(sizeof(double) * (size_t)cap);
	sp->ys = malloc(sizeof(double) * (size_t)cap);
	sp->types = malloc(sizeof(char) * (size_t)cap);
	sp->dists = malloc(sizeof(double) * (size_t)cap);
	if (!sp->xs || !sp->ys || !sp->types || !sp->dists)
		return (1);
	sp->cap = cap;
	return (0);
}

int	bonus_sprite_count_map(t_app *app)
{
	int		x;
	int		y;
	int		count;

	count = 0;
	y = 0;
	while (y < app->map.height)
	{
		x = 0;
		while (app->map.grid[y][x])
		{
			if (bonus_is_sprite_tile(app->map.grid[y][x]))
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	bonus_sprite_fill_from_map(t_app *app)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < app->map.height)
	{
		x = 0;
		while (app->map.grid[y][x])
		{
			c = app->map.grid[y][x];
			if (bonus_is_sprite_tile(c))
			{
				app->bonus.sprites.types[app->bonus.sprites.count] = c;
				app->bonus.sprites.xs[app->bonus.sprites.count] = x + 0.5;
				app->bonus.sprites.ys[app->bonus.sprites.count] = y + 0.5;
				app->bonus.sprites.count++;
			}
			x++;
		}
		y++;
	}
}
