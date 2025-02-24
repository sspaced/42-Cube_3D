/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:49:52 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/24 14:22:30 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	is_direction(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'O')
		return (1);
	return (0);
}

static int	get_player_angle(char direction)
{
	if (direction == 'N')
		return (270);
	if (direction == 'S')
		return (90);
	if (direction == 'E')
		return (0);
	if (direction == 'W')
		return (180);
	return (0);
}

static int	find_direction(char *str)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (is_direction(str[i]))
		{
			x = i;
			break ;
		}
		i++;
	}
	return (x);
}

void	set_player_pos_dir(t_data *data)
{
	int	x;
	int	y;

	if (!data)
		return ;
	if (!data->map.map_array)
		return ;
	x = 0;
	y = 0;
	while (data->map.map_array[y])
	{
		x = find_direction(data->map.map_array[y]);
		if (x != 0)
			break ;
		y++;
	}
	data->player.direction = get_player_angle(data->map.map_array[y][x]);
	data->player.x = x + .5;
	data->player.y = y + .5;
}
