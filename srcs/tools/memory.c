/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:59:59 by dbouizem          #+#    #+#             */
/*   Updated: 2026/03/31 17:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	free_app(t_app *app)
{
	free(app->config.tex_no);
	free(app->config.tex_so);
	free(app->config.tex_we);
	free(app->config.tex_ea);
	free_split(app->file_lines);
	app->file_lines = NULL;
}
