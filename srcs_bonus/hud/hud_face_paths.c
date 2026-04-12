/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_face_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouizem <djihane.bouizem@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:00:00 by dbouizem          #+#    #+#             */
/*   Updated: 2026/04/11 12:00:00 by dbouizem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char	*bonus_face_straight_path(int i, int j)
{
	static const char	*paths[5][3] = {
	{"textures/bonus/player/stfst00.xpm", "textures/bonus/player/stfst01.xpm",
		"textures/bonus/player/stfst02.xpm"},
	{"textures/bonus/player/stfst10.xpm", "textures/bonus/player/stfst11.xpm",
		"textures/bonus/player/stfst12.xpm"},
	{"textures/bonus/player/stfst20.xpm", "textures/bonus/player/stfst21.xpm",
		"textures/bonus/player/stfst22.xpm"},
	{"textures/bonus/player/stfst30.xpm", "textures/bonus/player/stfst31.xpm",
		"textures/bonus/player/stfst32.xpm"},
	{"textures/bonus/player/stfst40.xpm", "textures/bonus/player/stfst41.xpm",
		"textures/bonus/player/stfst42.xpm"}};

	return (paths[i][j]);
}

const char	*bonus_face_left_path(int i)
{
	static const char	*paths[5] = {
		"textures/bonus/player/stftl00.xpm",
		"textures/bonus/player/stftl10.xpm",
		"textures/bonus/player/stftl20.xpm",
		"textures/bonus/player/stftl30.xpm",
		"textures/bonus/player/stftl40.xpm"};

	return (paths[i]);
}

const char	*bonus_face_right_path(int i)
{
	static const char	*paths[5] = {
		"textures/bonus/player/stftr00.xpm",
		"textures/bonus/player/stftr10.xpm",
		"textures/bonus/player/stftr20.xpm",
		"textures/bonus/player/stftr30.xpm",
		"textures/bonus/player/stftr40.xpm"};

	return (paths[i]);
}

const char	*bonus_face_ouch_path(int i)
{
	static const char	*paths[5] = {
		"textures/bonus/player/stfouch0.xpm",
		"textures/bonus/player/stfouch1.xpm",
		"textures/bonus/player/stfouch2.xpm",
		"textures/bonus/player/stfouch3.xpm",
		"textures/bonus/player/stfouch4.xpm"};

	return (paths[i]);
}

const char	*bonus_face_kill_path(int i)
{
	static const char	*paths[5] = {
		"textures/bonus/player/stfkill0.xpm",
		"textures/bonus/player/stfkill1.xpm",
		"textures/bonus/player/stfkill2.xpm",
		"textures/bonus/player/stfkill3.xpm",
		"textures/bonus/player/stfkill4.xpm"};

	return (paths[i]);
}
