/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elleroux <elleroux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:39:31 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/03 15:56:10 by elleroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_foward(t_player *player, t_map *map, double angle)
{
	double	new_x;
	double	new_y;

	new_x = player->x + cos(angle) * MOVE_SPEED;
	new_y = player->y + sin(angle) * MOVE_SPEED;
	if (!check_collision(map, new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

void	move_left(t_player *player, t_map *map, double angle)
{
	double	new_x;
	double	new_y;

	new_x = player->x + sin(angle) * MOVE_SPEED;
	new_y = player->y - cos(angle) * MOVE_SPEED;
	if (!check_collision(map, new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

void	move_backward(t_player *player, t_map *map, double angle)
{
	double	new_x;
	double	new_y;

	new_x = player->x - cos(angle) * MOVE_SPEED;
	new_y = player->y - sin(angle) * MOVE_SPEED;
	if (!check_collision(map, new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

void	move_right(t_player *player, t_map *map, double angle)
{
	double	new_x;
	double	new_y;

	new_x = player->x - sin(angle) * MOVE_SPEED;
	new_y = player->y + cos(angle) * MOVE_SPEED;
	if (!check_collision(map, new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}
