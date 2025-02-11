#include	"cube.h"

int	check_file_path(char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
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
	char *info_value;
	status = 0;
	line = ft_strtrim(line, "\n");
	if (!line)
		return (0);
	line_split = ft_split(line, ' ');
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

int is_only_space(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int check_info_complete(t_map_info *map_info)
{
	if (map_info->no == NULL || map_info->so == NULL || map_info->we == NULL || map_info->ea == NULL)
		return (0);
	return (1);
}

static int	ft_strlen_until(char *str, char until)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == until)
			break ;
		i++;
	}
	return (i);
}

static char *ft_strdup_until(char *str, char until)
{
	char	*str_b;
	int		str_len;

	if (!str)
		return (NULL);
	str_len = ft_strlen_until((char *)str, until);
	str_b = (char *)malloc(str_len * sizeof(char) + 1);
	if (!str_b)
		return (NULL);
	while (*str)
	{
		if (*str == until)
			break ;
		*str_b++ = *str++;
	}
	*str_b = '\0';
	return (str_b -= str_len);
}

typedef	struct s_map_v2 {
	char	**map_array;
	float	map_height;
	float	map_width;
	int		current_line_count;
} t_map_v2;

int refill_map(char *line, char **array_map, char **new_array_map)	
{
	int i;
	
	if (!line || !new_array_map)
		return (0);
	
	i = 0;
	if (array_map == NULL)
	{
		if (!(new_array_map[0] = ft_strdup_until(line, '\n')))
			return (0);
		new_array_map[1] = NULL;
	}
	else
	{
		while (array_map[i] != NULL)
		{
			new_array_map[i] = ft_strdup_until(array_map[i], '\n');
			i++;
		}
		if (!(new_array_map[i] = ft_strdup_until(line, '\n')))
			return (0);
		new_array_map[i + 1] = NULL;
	}
	return (1);
}

int append_map_lines(char *line, t_map *map)
{
	char **new_array_map = NULL;
	new_array_map = malloc(sizeof(char *) * (map->current_line_count + 2));
	if (!new_array_map)
		return (0);
	if (!refill_map(line, map->map_array, new_array_map))
	{
		free(new_array_map);
		return (0);
	}
	clear_array(map->map_array);
	map->map_array = new_array_map;
	map->current_line_count++;
	return (1);
}

int check_player(char **map_array)
{
	int i;
	int j;
	int player_count;

	i = 0;
	j = 0;
	player_count = 0;
	while (map_array[i] != NULL)
	{
		while (map_array[i][j] != '\0')
		{
			if (map_array[i][j] == 'N' || map_array[i][j] == 'S' || map_array[i][j] == 'W' || map_array[i][j] == 'E')
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

int zero_check(char current)
{
	if (current == '1')
		return (1);
	if (current == ' ')
		return (0);
	return (-1);
}

int check_right(int x, char *map_line)
{
	while (map_line[x] != '\0')
	{
		if (zero_check(map_line[x]) != -1)
			return (zero_check(map_line[x]));
		x++;
	}
	return (0);
}

int check_left(int x, char *map_line)
{
	while (x >= 0)
	{
		if (zero_check(map_line[x]) != -1)
			return (zero_check(map_line[x]));
		x--;
	}
	return (0);
}

int check_up(int x, int y, char **map_array)
{
	while (y >= 0)
	{
		if (y - 1 >= 0 && ft_strlen(map_array[y - 1]) > x)
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

int check_down(int x, int y, char **map_array)
{
	while (map_array[y] != NULL)
	{
		if (map_array[y + 1] != NULL && ft_strlen(map_array[y + 1]) > x)
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

int check_close_map(char **map_array)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (map_array[i] != NULL)
	{
		while (map_array[i][j] != '\0')
		{
			if (map_array[i][j] == '0')	
			{
				if (!check_right(j, map_array[i]) || !check_left(j, map_array[i]) || !check_up(j, i, map_array) || !check_down(j, i, map_array))
					return (printf("Map not closed ! at line %d, column %d\n", i, j), 0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

void display_map_info_test(t_map_info *map_info)
{
	printf("NO: %s\n", map_info->no);
	printf("SO: %s\n", map_info->so);
	printf("WE: %s\n", map_info->we);
	printf("EA: %s\n", map_info->ea);
	printf("F: %d, %d, %d\n", map_info->f[0], map_info->f[1], map_info->f[2]);
	printf("C: %d, %d, %d\n", map_info->c[0], map_info->c[1], map_info->c[2]);
}

void display_map_test(char **map_array)
{
	int i;

	i = 0;
	while (map_array[i] != NULL)
	{
		printf("%s\n", map_array[i]);
		i++;
	}
}


int extract_map(char *line, t_data *data)
{
	int map_part;
	int only_space;

	map_part = contain_map_part(line);
	only_space = is_only_space(line);
	if (!map_part && !only_space)
		return (printf("Invalid line : %s\n", line), 0);
	else
	{
		if (!only_space)
		{
			if (append_map_lines(line, &data->map))
			{
				//add protection
			}
		}
	}
	return (1);
}

int parser_check(t_data *data)
{
	if (!check_info_complete(&data->map_info))
		return (printf("Missing info in map !\n"), 0);
	if (!check_player(data->map.map_array))
		return (printf("Invalid player !\n"), 0);
	if (!check_close_map(data->map.map_array))
		return (0);
	return (1);
}
 int extractor(int fd, t_data *data)
 {
	int		i;
	char	*info_types[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	char	*line;
	char	*info;

	i = 0;
	info = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if ((info = search_info(line, info_types)) != NULL)
		{
			if (!extract_info(line, info, &data->map_info))
				return (printf("Err with [%s] at line %d\n", info, i), 0);
		}
		else
			extract_map(line, data);
		free(line);
		i++;
	}
	return (1);
 }

int parser(char **argv, t_data *data)
{
	int		fd;

	if (!check_file_path(argv[1]))
		return (ft_putstr_fd("Invalid path\n", 2), 0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error opening file\n", 2), 0);
	extractor(fd, data);
	if (!parser_check(data))
		return (close(fd), 0);
	return (close(fd), 1);
}
