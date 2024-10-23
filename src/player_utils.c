#include "cube.h"

static int	is_direction(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'O')
		return (1);
	return (0);
}

static int find_direction(char *str)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (is_direction(str[i]))
		{
			x = i;
			printf("hello\n");
			break ;
		}
		i++;
	}
	return (x);
}

void	set_player_pos_dir(t_data *data)
{
	int	x;
	int	y;

	if (!data)
		return ;
	if (!data->map.map_array)
		return ;
	
	x = 0;
	y = 0;
	while (data->map.map_array[y])
	{
		x = find_direction(data->map.map_array[y]);
		if (x != 0)
			break ;
		y++;
	}
	data->player.direction = data->map.map_array[y][x];
	data->player.x = x + 1;
	data->player.y = data->map.map_height - y;
}
