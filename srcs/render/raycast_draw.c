/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/15 10:06:15 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_tex_pixel(t_img *tex, int tx, int ty)
{
	char	*dst;
	int		color;

	if (tx < 0 || tx >= tex->width || ty < 0 || ty >= tex->height)
		return (0);
	dst = tex->addr + (ty * tex->line_len + tx * (tex->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

static t_img	*select_texture(t_app *app, t_ray *ray)
{
	if (ray->wall_face == 'N')
		return (&app->tex_no);
	else if (ray->wall_face == 'S')
		return (&app->tex_so);
	else if (ray->wall_face == 'E')
		return (&app->tex_ea);
	else if (ray->wall_face == 'W')
		return (&app->tex_we);
	return (NULL);
}

static int	calculate_tex_x(double wall_x, int tex_width)
{
	int	tex_x;

	if (wall_x < 0.0)
		wall_x = 0.0;
	if (wall_x >= 1.0)
		wall_x = 0.999999;
	tex_x = (int)(wall_x * tex_width);
	if (tex_x >= tex_width)
		tex_x = tex_width - 1;
	return (tex_x);
}

static int	calculate_tex_y(int y, int draw_start, int line_height,
	int tex_height)
{
	int		tex_y;
	double	fraction;

	if (line_height <= 0)
		return (0);
	fraction = (double)(y - draw_start) / (double)line_height;
	tex_y = (int)(fraction * tex_height);
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= tex_height)
		tex_y = tex_height - 1;
	return (tex_y);
}

void	draw_wall_column(t_app *app, t_ray *ray, int x)
{
	int		y;
	int		tex_x;
	int		tex_y;
	int		color;
	t_img	*tex;

	tex = select_texture(app, ray);
	if (!tex)
		return ;
	tex_x = calculate_tex_x(ray->wall_x, tex->width);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = calculate_tex_y(y, ray->draw_start, ray->line_height,
				tex->height);
		color = get_tex_pixel(tex, tex_x, tex_y);
		put_pixel(&app->frame, x, y, color);
		y++;
	}
}
