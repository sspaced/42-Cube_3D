/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:08:27 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/24 14:22:00 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	count_map_lines(char *file_path)
{
	char	*line;
	int		fd;
	int		line_count;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (-1);
	line_count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line_count++;
		free(line);
	}
	close(fd);
	return (line_count);
}

static char	**allocate_map(int line_count)
{
	char	**map;

	if (line_count <= 0)
		return (NULL);
	map = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!map)
		return (NULL);
	return (map);
}

static int	fill_map(char **map, char *file_path)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (0);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map[i] = ft_strdup_until(line, '\n');
		if (!map[i])
			return (free(line), close(fd), 0);
		free(line);
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (1);
}

void	free_map_error(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	**read_map_file(char *file_path)
{
	char	**map;
	int		line_count;

	if (!file_path)
		return (NULL);
	line_count = count_map_lines(file_path);
	if (line_count <= 0)
		return (NULL);
	map = allocate_map(line_count);
	if (!map)
		return (NULL);
	if (!fill_map(map, file_path))
	{
		free_map_error(map);
		return (NULL);
	}
	return (map);
}
