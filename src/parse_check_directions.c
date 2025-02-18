/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check_directions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:49:52 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/18 15:15:27 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	zero_check(char current)
{
	if (current == '1')
		return (1);
	if (current == ' ')
		return (0);
	return (-1);
}

int	check_right(int x, char *map_line)
{
	while (map_line[x] != '\0')
	{
		if (zero_check(map_line[x]) != -1)
			return (zero_check(map_line[x]));
		x++;
	}
	return (0);
}

int	check_left(int x, char *map_line)
{
	while (x >= 0)
	{
		if (zero_check(map_line[x]) != -1)
			return (zero_check(map_line[x]));
		x--;
	}
	return (0);
}

int	check_up(int x, int y, char **map_array)
{
	while (y >= 0)
	{
		if (y - 1 >= 0 && (int)ft_strlen(map_array[y - 1]) > x)
		{
			if (zero_check(map_array[y - 1][x]) != -1)
				return (zero_check(map_array[y - 1][x]));
		}
		else
			return (0);
		y--;
	}
	return (0);
}

int	check_down(int x, int y, char **map_array)
{
	while (map_array[y] != NULL)
	{
		if (map_array[y + 1] != NULL && (int)ft_strlen(map_array[y + 1]) > x)
		{
			if (zero_check(map_array[y + 1][x]) != -1)
				return (zero_check(map_array[y + 1][x]));
		}
		else
			return (0);
		y++;
	}
	return (0);
}
