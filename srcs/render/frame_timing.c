/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_timing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 05:20:00 by brrr1            #+#    #+#             */
/*   Updated: 2026/04/05 05:20:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

static double	get_time_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((double)tv.tv_sec + (double)tv.tv_usec / 1000000.0);
}

void	update_frame_timing(t_app *app)
{
	double	now;

	now = get_time_seconds();
	if (app->last_frame_time <= 0.0)
		app->delta_time = FRAME_DT_DEFAULT;
	else
	{
		app->delta_time = now - app->last_frame_time;
		if (app->delta_time < 0.0)
			app->delta_time = FRAME_DT_DEFAULT;
		else if (app->delta_time > FRAME_DT_MAX)
			app->delta_time = FRAME_DT_MAX;
	}
	app->last_frame_time = now;
	app->frame_count++;
}
