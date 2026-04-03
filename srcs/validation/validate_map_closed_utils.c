/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_closed_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brrr1 <brrr1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by brrr1             #+#    #+#             */
/*   Updated: 2026/04/03 00:00:00 by brrr1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	enqueue(t_node **queue, int x, int y)
{
	t_node	*new_node;
	t_node	*temp;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return ;
	new_node->x = x;
	new_node->y = y;
	new_node->next = NULL;
	if (!*queue)
		*queue = new_node;
	else
	{
		temp = *queue;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

int	dequeue(t_node **queue, int *x, int *y)
{
	t_node	*temp;

	if (!*queue)
		return (0);
	temp = *queue;
	*x = temp->x;
	*y = temp->y;
	*queue = temp->next;
	free(temp);
	return (1);
}

void	free_queue(t_node *queue)
{
	t_node	*temp;

	while (queue)
	{
		temp = queue;
		queue = queue->next;
		free(temp);
	}
}

void	init_directions(int *dx, int *dy)
{
	dy[0] = -1;
	dy[1] = 1;
	dy[2] = 0;
	dy[3] = 0;
	dx[0] = 0;
	dx[1] = 0;
	dx[2] = 1;
	dx[3] = -1;
}
