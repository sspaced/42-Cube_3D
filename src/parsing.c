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

int set_map_cardinal_info(char **map_info_field, char *info_value)
{
	if ((*map_info_field) == NULL)
	{
		*map_info_field = info_value;
		return (1);
	}
	return (0);
}

int is_digit(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int is_valid_color(char *info_value)
{
	char **splited_color;
	int i;

	i = 0;
	splited_color = ft_split(info_value, ',');
	if (splited_color == NULL || array_size(splited_color) != 3)
		return (0);
	while (splited_color[i] != NULL)
	{
		if (!is_digit(splited_color[i]) || ft_atoi(splited_color[i]) < 0 || ft_atoi(splited_color[i]) > 255)
		{
			clear_array(splited_color);
			return (0);
		}
		i++;
	}
	clear_array(splited_color);
	return (1);
}	

int set_map_color_info(int map_info_field[3], char *info_value)
{
	if (!is_valid_color(info_value))
		return (0);
	map_info_field[0] = ft_atoi(info_value);
	info_value += 4;
	map_info_field[1] = ft_atoi(info_value);
	info_value += 4;
	map_info_field[2] = ft_atoi(info_value);
	return (1);
}


int map_info_setter(char *info_type, char *info_value, t_map_info *map_info)
{
	if (!ft_strncmp(info_type, "NO", 2))
		return (set_map_cardinal_info(&map_info->no, info_value));
	else if (!ft_strncmp(info_type, "SO", 2))
		return (set_map_cardinal_info(&map_info->so, info_value));
	else if (!ft_strncmp(info_type, "WE", 2))
		return (set_map_cardinal_info(&map_info->we, info_value));
	else if (!ft_strncmp(info_type, "EA", 2))
		return (set_map_cardinal_info(&map_info->ea, info_value));
	else if (!ft_strncmp(info_type, "F", 1))
		return (set_map_color_info(map_info->f, info_value));
	else if (!ft_strncmp(info_type, "C", 1))
		return (set_map_color_info(map_info->c, info_value));
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

int check_info_complete(t_map_info *map_info)
{
	if (!map_info->no)
	{
		printf("NO is missing\n");
		return (0);
	}
	printf("NO is set\n");
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
	int i = 0;

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
				return (printf("Err with [%s] at line %d\n", info, i), 0);
			// if (check_info_complete(&map_info))
			// 	return (printf("Missing info in map !\n"), 0);
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
		i++;
	}

	printf("NO: %s\n", map_info.no);
	printf("SO: %s\n", map_info.so);
	printf("WE: %s\n", map_info.we);
	printf("EA: %s\n", map_info.ea);
	printf("F: %d, %d, %d\n", map_info.f[0], map_info.f[1], map_info.f[2]);
	printf("C: %d, %d, %d\n", map_info.c[0], map_info.c[1], map_info.c[2]);
	close(fd);
	return (1);
}
