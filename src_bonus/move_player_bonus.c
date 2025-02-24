/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:39:31 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/24 14:08:13 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	check_collision(t_map *map, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_x < 0 || map_y < 0 || map_x >= map->map_width
		|| map_y >= map->map_height || map->map_array[map_y][map_x] == '1')
		return (1);
	return (0);
}

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
