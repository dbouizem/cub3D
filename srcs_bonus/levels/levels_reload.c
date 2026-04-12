/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_reload.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 22:15:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/09 22:15:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_level_data(t_app *app)
{
	bonus_doors_shutdown(app);
	bonus_pickups_shutdown(app);
	bonus_destroy_level_tex(app, &app->tex_no);
	bonus_destroy_level_tex(app, &app->tex_so);
	bonus_destroy_level_tex(app, &app->tex_we);
	bonus_destroy_level_tex(app, &app->tex_ea);
	free(app->config.tex_no);
	free(app->config.tex_so);
	free(app->config.tex_we);
	free(app->config.tex_ea);
	app->config.tex_no = NULL;
	app->config.tex_so = NULL;
	app->config.tex_we = NULL;
	app->config.tex_ea = NULL;
	free_split(app->map.grid);
	app->map.grid = NULL;
	app->map.height = 0;
}

static int	cleanup_next_load(t_app *app, t_img tex[4], t_app *next)
{
	bonus_destroy_level_tex(app, &tex[0]);
	bonus_destroy_level_tex(app, &tex[1]);
	bonus_destroy_level_tex(app, &tex[2]);
	bonus_destroy_level_tex(app, &tex[3]);
	bonus_doors_shutdown(next);
	bonus_pickups_shutdown(next);
	return (1);
}

static int	apply_next_level(t_app *app, t_app *next)
{
	t_img	tex[4];

	ft_bzero(tex, sizeof(tex));
	if (bonus_load_next_level_textures(app, next, tex) != 0)
		return (1);
	if (bonus_doors_init(next) != 0)
		return (cleanup_next_load(app, tex, next));
	if (bonus_pickups_rebuild(next) != 0)
		return (cleanup_next_load(app, tex, next));
	if (bonus_sprite_ensure_cap(&app->bonus.sprites,
			bonus_pickups_count_active(next)) != 0)
		return (cleanup_next_load(app, tex, next));
	free_level_data(app);
	bonus_transfer_next_level(app, next, tex);
	app->ceiling_color = (app->config.ceiling_rgb[0] << 16)
		| (app->config.ceiling_rgb[1] << 8) | app->config.ceiling_rgb[2];
	app->floor_color = (app->config.floor_rgb[0] << 16)
		| (app->config.floor_rgb[1] << 8) | app->config.floor_rgb[2];
	if (bonus_sprites_rebuild(app) != 0)
		return (1);
	init_player_vectors(app);
	ft_bzero(&app->input, sizeof(app->input));
	return (0);
}

int	bonus_load_next_level(t_app *app)
{
	t_app			next;
	t_bonus_levels	*levels;
	int				next_i;

	if (!app)
		return (1);
	levels = &app->bonus.levels;
	if (!levels->active || levels->current + 1 >= levels->count)
		return (1);
	next_i = levels->current + 1;
	init_app(&next);
	if (parse_file(&next, levels->paths[next_i]) != 0)
		return (free_app(&next), 1);
	if (apply_next_level(app, &next) != 0)
		return (free_app(&next), 1);
	free_app(&next);
	levels->current = next_i;
	return (0);
}
