#include	"cube.h"

int	check_file_path(char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = strlen(path);
	if (len < 4)
		return (0);
	if (path[len - 4] != '.' || path[len - 3] != 'c' || 
		path[len - 2] != 'u' || path[len - 1] != 'b')
		return (0);
	return (1);
}


int contain_info(char *line, char *info_type)
{
	int i;
	int u;
	int found;

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
				break;
			}
			u++;
		}
		else
			u = 0;
		i++;
	}
	return (found);
}

int is_map_part(char element)
{
	if (element == '1' || element == '0' || element == 'N' 
			|| element == 'S' || element == 'W' 
			|| element == 'E' || element == ' ' 
			|| element == '\n')
		return (1);
	return (0);
}

int contain_map_part(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!is_map_part(line[i]))
			return (0);
		i++;
	}
	return (1);
}

char *search_info(char *line, char **info_type)
{
	int i;
	char *info;

	i = 0;
	info = NULL;
	while (info_type[i] != NULL)
	{
		if (contain_info(line, info_type[i]))
		{
			info = info_type[i];
			break;
		}
		i++;
	}
	return (info);
}
void init_map_info(t_map_info *map_info)
{
	map_info->no = NULL;
	map_info->so = NULL;
	map_info->we = NULL;
	map_info->ea = NULL;
	map_info->f = NULL;
	map_info->c = NULL;
}

int array_size(char **array)
{
	int i;

	i = 0;
	if (!array)
		return (0);
	while (array[i] != NULL)
		i++;
	return (i);
}

void clear_array(char **array)
{
	int i;

	i = 0;
	if (!array)
		return;
	while (array[i] != NULL)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}

int set_map_info_value(char **map_info_field, char *info_value)
{
	if ((*map_info_field) == NULL)
	{
		*map_info_field = info_value;
		return (1);
	}
	return (0);
}

int map_info_setter(char *info_type, char *info_value, t_map_info *map_info)
{
	if (!ft_strncmp(info_type, "NO", 2))
		return (set_map_info_value(&map_info->no, info_value));
	else if (!ft_strncmp(info_type, "SO", 2))
		return (set_map_info_value(&map_info->so, info_value));
	else if (!ft_strncmp(info_type, "WE", 2))
		return (set_map_info_value(&map_info->we, info_value));
	else if (!ft_strncmp(info_type, "EA", 2))
		return (set_map_info_value(&map_info->ea, info_value));
	else if (!ft_strncmp(info_type, "F", 1))
		return (set_map_info_value(&map_info->f, info_value));
	else if (!ft_strncmp(info_type, "C", 1))
		return (set_map_info_value(&map_info->c, info_value));
	return (0);
}

int extract_info(char *line, char *info_type, t_map_info *map_info)
{
	char **line_split;
	int status;

	status = 0;
	line = ft_strtrim(line, "\n");
	line_split = ft_split(line, ' ');
	if (!line_split || !line)
		return (0);
	if (array_size(line_split) == 2)
		status = map_info_setter(line_split[0], ft_strdup(line_split[1]), map_info);
	clear_array(line_split);
	return (status);
}

int is_only_space(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int parser(char **argv)
{
	if (!check_file_path(argv[1]))
		return (ft_putstr_fd("Invalid path\n", 2), 0);

	t_map_info	map_info;
	char	*line;
	char	*info = NULL;
	int		fd;
	char *info_type[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	int info_nb;

	init_map_info(&map_info);

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error opening file\n", 2), 0);

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if ((info = search_info(line, info_type)) != NULL)
		{
			if (!extract_info(line, info, &map_info))
				return (printf("Too many [%s] declaration in map !\n", info), 0);
			// check if all info are set
			// check if F an C value are valid
		}
		else
		{
			if (!contain_map_part(line) && !is_only_space(line))
			{
				return (printf("Invalid line : %s\n", line), 0);
			}
			else
			{
				// check if map is valid
				// check if map is last
			}
		}
		free(line);
	}

	printf("NO: %s\n", map_info.no);
	printf("SO: %s\n", map_info.so);
	printf("WE: %s\n", map_info.we);
	printf("EA: %s\n", map_info.ea);
	printf("F: %s\n", map_info.f);
	printf("C: %s\n", map_info.c);
	close(fd);
	return (1);
}
