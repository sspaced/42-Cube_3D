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

int check_info(char *line, char **info_type)
{
	int i;
	int found;

	i = 0;
	found = 0;
	while (info_type[i] != NULL)
	{
		if (contain_info(line, info_type[i]))
		{
			found = 1;
			printf("%s\n", info_type[i]);
		}
		i++;
	}
	return (found);
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

int parser(char **argv)
{
	if (!check_file_path(argv[1]))
		return (ft_putstr_fd("Invalid path\n", 2), 0);

	t_map_info	map_info;

	init_map_info(&map_info);
	char	*line;
	int		fd;
	char *info[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error opening file\n", 2), 0);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		
		if (!check_info(line, info))
		{
			if (!contain_map_part(line))
				printf("nothing\n");
			else
				printf("map part\n");
		}
		free(line);
	}
	close(fd);
	// make finder for NO, SO, WE, EA, F, C
	return (1);
}
