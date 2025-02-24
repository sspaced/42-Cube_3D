/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:49:52 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/18 15:35:54 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	start(char **new_array_map, char *line)
{
	new_array_map[0] = ft_strdup_until(line, '\n');
	if (!new_array_map[0])
		return (0);
	new_array_map[1] = NULL;
	return (1);
}

static int	refill_map(char *line, char **array_map, char **new_array_map)
{
	int	i;

	if (!line || !new_array_map)
		return (0);
	i = 0;
	if (array_map == NULL)
	{
		if (!start(new_array_map, line))
			return (0);
	}
	else
	{
		while (array_map[i] != NULL)
		{
			new_array_map[i] = ft_strdup_until(array_map[i], '\n');
			if (!new_array_map[i])
				return (clear_array(new_array_map), 0);
			i++;
		}
		new_array_map[i] = ft_strdup_until(line, '\n');
		if (!new_array_map[i])
			return (clear_array(new_array_map), 0);
		new_array_map[i + 1] = NULL;
	}
	return (1);
}

static int	append_map_lines(char *line, t_map *map)
{
	char	**new_array_map;

	new_array_map = malloc(sizeof(char *) * (map->current_line_count + 2));
	if (!new_array_map)
		return (0);
	if (!refill_map(line, map->map_array, new_array_map))
		return (0);
	clear_array(map->map_array);
	map->map_array = new_array_map;
	map->current_line_count++;
	return (1);
}

int	extract_map(char *line, t_data *data)
{
	int	map_part;
	int	only_space;

	map_part = contain_map_part(line);
	only_space = is_only_space(line);
	if (!map_part && !only_space)
	{
		ft_putstr_fd("Invalid line : ", 2);
		ft_putstr_fd(line, 2);
		ft_putstr_fd("\n", 2);
		return (0);
	}
	else
	{
		if (!only_space)
		{
			if (!append_map_lines(line, &data->map))
				return (0);
		}
		else if (data->map.current_line_count != 0)
			return (printf("only space at line %d\n",
					data->map.current_line_count), 0);
	}
	return (1);
}
