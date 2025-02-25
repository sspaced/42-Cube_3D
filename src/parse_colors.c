/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:49:52 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/25 18:16:19 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	is_valid_color(char *info_value)
{
	char	**splited_color;
	int		i;

	i = 0;
	splited_color = ft_split(info_value, ',');
	if (splited_color == NULL || array_size(splited_color) != 3)
		return (clear_array(splited_color), 0);
	while (splited_color[i] != NULL)
	{
		if (!is_digit(splited_color[i]) || ft_atoi(splited_color[i]) < 0
			|| ft_atoi(splited_color[i]) > 255)
		{
			clear_array(splited_color);
			return (0);
		}
		i++;
	}
	clear_array(splited_color);
	return (1);
}

int	set_map_color_info(int *map_info_field, char *info_value)
{
	char	*buff;

	buff = info_value;
	if (!is_valid_color(info_value))
		return (free(buff), 0);
	if (*map_info_field != -1)
		return (free(buff), 0);
	*map_info_field = ft_atoi(info_value);
	*map_info_field = *map_info_field << 8;
	info_value = ft_strchr(info_value, ',') + 1;
	*map_info_field += ft_atoi(info_value);
	*map_info_field = *map_info_field << 8;
	info_value = ft_strchr(info_value, ',') + 1;
	*map_info_field += ft_atoi(info_value);
	free(buff);
	return (1);
}
