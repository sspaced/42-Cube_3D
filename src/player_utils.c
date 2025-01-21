#include "cub.h"

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
	data->player.direction = get_player_angle(data->map.map_array[y][x]);
	data->player.x = x + .5;
	data->player.y = y + .5;
}

// void set_player_pos_dir(t_data *data)
// {
//     int y = 0;
//     while (y < data->map.map_height)
//     {
//         int x = 0;
//         while (x < data->map.map_width)
//         {
//             if (data->map.map_array[y][x] == 'N' || 
//                 data->map.map_array[y][x] == 'S' || 
//                 data->map.map_array[y][x] == 'E' || 
//                 data->map.map_array[y][x] == 'W')
//             {
//                 data->player.x = x + 0.5;  // Centre du carré
//                 data->player.y = y + 0.5;  // Centre du carré
//                 // Convertir la direction en angle
//                 switch (data->map.map_array[y][x])
//                 {
//                     case 'N': data->player.angle = 270; break;
//                     case 'S': data->player.angle = 90; break;
//                     case 'E': data->player.angle = 0; break;
//                     case 'W': data->player.angle = 180; break;
//                 }
//                 data->map.map_array[y][x] = '0';  // Libérer la case
//                 return;
//             }
//             x++;
//         }
//         y++;
//     }
// }
