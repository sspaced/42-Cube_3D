/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:39:31 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/25 18:44:27 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	check_collision(t_map *map, double new_x, double new_y, double angle)
{
	if (angle == 0)
		new_x += 0.1;
	else if (angle == 90)
		new_y += 0.1;
	else if (angle == 180)
		new_x -= 0.1;
	else if (angle == 270)
		new_y -= 0.1;
	if (new_x < 0 || new_y < 0 || new_x >= map->map_width
		|| new_y >= map->map_height || map->map_array[(int)new_y][(int)new_x] == '1')
		return (1);
	return (0);
}

void	move_foward(t_player *player, t_map *map, double angle)
{
	double	new_x;
	double	new_y;

	new_x = player->x + cos(angle) * MOVE_SPEED;
	new_y = player->y + sin(angle) * MOVE_SPEED;
	if (!check_collision(map, new_x, new_y, angle))
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
	if (!check_collision(map, new_x, new_y, angle))
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
	if (!check_collision(map, new_x, new_y, angle))
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
	if (!check_collision(map, new_x, new_y, angle))
	{
		player->x = new_x;
		player->y = new_y;
	}
}
