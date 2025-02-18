/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:08:27 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/18 15:44:29 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	check_file_path(char *path)
{
	size_t	len;
	int		fd;

	if (!path)
		return (ft_putstr_fd("Error: NULL path\n", 2), 0);
	len = ft_strlen(path);
	if (len < 4)
		return (ft_putstr_fd("Error: Path too short\n", 2), 0);
	if (path[len - 4] != '.' || path[len - 3] != 'c' || path[len - 2] != 'u'
		|| path[len - 1] != 'b')
		return (ft_putstr_fd("Error: Invalid file extension (must be .cub)\n",
				2), 0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error: Cannot open file\n", 2), 0);
	close(fd);
	return (1);
}

static int	parser_check(t_data *data)
{
	if (data->map.map_array == NULL)
		return (0);
	if (!check_info_complete(&data->map.map_info))
		return (ft_putstr_fd("Missing info in map !\n", 2), 0);
	if (!check_player(data->map.map_array))
		return (ft_putstr_fd("Invalid player !\n", 2), 0);
	if (!check_close_map(data->map.map_array))
		return (0);
	return (1);
}

static int	extractor(int fd, t_data *data)
{
	int			i;
	static char	*info_types[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	char		*line;
	char		*info;

	i = 0;
	info = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		info = search_info(line, info_types);
		if (info != NULL)
		{
			if (!extract_info(line, &data->map.map_info))
				return (err_msg(info, i), free(line), 0);
		}
		else if (!extract_map(line, data))
			return (free(line), 0);
		free(line);
		i++;
	}
	return (1);
}

int	parser(char **argv, t_data *data)
{
	int	fd;

	if (!check_file_path(argv[1]))
		return (ft_putstr_fd("Invalid path\n", 2), 0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error opening file\n", 2), 0);
	if (!extractor(fd, data))
		return (close(fd), 0);
	if (!parser_check(data))
		return (close(fd), 0);
	return (close(fd), 1);
}
