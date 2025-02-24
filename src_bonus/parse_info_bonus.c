/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:49:52 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/20 14:48:23 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	set_map_cardinal_info(char **map_info_field, char *info_value)
{
	if ((*map_info_field) == NULL)
	{
		*map_info_field = info_value;
		return (1);
	}
	free(info_value);
	return (0);
}

static int	map_info_setter(char *info_type, char *info_value,
		t_map_info *map_info)
{
	int	info_type_len;

	info_type_len = ft_strlen(info_type);
	if (!ft_strncmp(info_type, "NO", 2) && info_type_len == 2)
		return (set_map_cardinal_info(&map_info->no, info_value));
	else if (!ft_strncmp(info_type, "SO", 2) && info_type_len == 2)
		return (set_map_cardinal_info(&map_info->so, info_value));
	else if (!ft_strncmp(info_type, "WE", 2) && info_type_len == 2)
		return (set_map_cardinal_info(&map_info->we, info_value));
	else if (!ft_strncmp(info_type, "EA", 2) && info_type_len == 2)
		return (set_map_cardinal_info(&map_info->ea, info_value));
	else if (!ft_strncmp(info_type, "F", 1) && info_type_len == 1)
		return (set_map_color_info(&map_info->f, info_value));
	else if (!ft_strncmp(info_type, "C", 1) && info_type_len == 1)
		return (set_map_color_info(&map_info->c, info_value));
	return (free(info_value), 0);
}

static int	contain_info(char *line, char *info_type)
{
	int	i;
	int	u;
	int	found;

	i = 0;
	u = 0;
	found = 0;
	while (line[i] != '\0')
	{
		if (line[i] == info_type[u])
		{
			if (u == (int)strlen(info_type) - 1)
			{
				found = 1;
				break ;
			}
			u++;
		}
		else
			u = 0;
		i++;
	}
	return (found);
}

int	extract_info(char *line, t_map_info *map_info)
{
	char	**line_split;
	int		status;
	char	*info_value;

	status = 0;
	line = ft_strtrim(line, "\n");
	if (!line)
		return (0);
	line_split = ft_split(line, ' ');
	free(line);
	if (!line_split)
		return (clear_array(line_split), 0);
	info_value = ft_strdup(line_split[1]);
	if (!info_value)
		return (clear_array(line_split), 0);
	if (array_size(line_split) == 2)
		status = map_info_setter(line_split[0], info_value, map_info);
	clear_array(line_split);
	return (status);
}

char	*search_info(char *line, char **info_type)
{
	int		i;
	char	*info;

	i = 0;
	info = NULL;
	while (info_type[i] != NULL)
	{
		if (contain_info(line, info_type[i]))
		{
			info = info_type[i];
			break ;
		}
		i++;
	}
	return (info);
}
