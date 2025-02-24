/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_final_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:08:27 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/24 15:37:58 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_info_complete(t_map_info *map_info)
{
	if (map_info->no == NULL || map_info->so == NULL || map_info->we == NULL
		|| map_info->ea == NULL)
		return (0);
	return (1);
}

int	check_player(char **map_array)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	j = 0;
	player_count = 0;
	while (map_array[i] != NULL)
	{
		while (map_array[i][j] != '\0')
		{
			if (map_array[i][j] == 'N' || map_array[i][j] == 'S'
				|| map_array[i][j] == 'W' || map_array[i][j] == 'E')
				player_count++;
			j++;
		}
		j = 0;
		i++;
	}
	if (player_count != 1)
		return (0);
	return (1);
}

static	void	err_msg_2(int i)
{
	ft_putstr_fd("Map not closed ! at line ", 2);
	ft_putnbr_fd(i, 2);
	ft_putstr_fd(", column ", 2);
}

int	check_close_map(char **map_array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map_array[i] != NULL)
	{
		while (map_array[i][j] != '\0')
		{
			if (map_array[i][j] == '0')
			{
				if (!check_right(j, map_array[i]) || !check_left(j,
						map_array[i]) || !check_up(j, i, map_array)
					|| !check_down(j, i, map_array))
				{
					err_msg_2(i);
					return (ft_putnbr_fd(j, 2), ft_putstr_fd("\n", 2), 0);
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}
