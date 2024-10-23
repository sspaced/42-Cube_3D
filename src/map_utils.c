#include "cube.h"

void	set_map_height_width(t_data *data)
{
	int x;
	int y;
	int y_bis;

	if (!data)
		return ;
	if (!data->map.map_array)
		return ;
	x = 0;
	y = 0;
	y_bis = 0;
	while (data->map.map_array[x])
	{
		while (data->map.map_array[x][y])
			y++;
		y_bis = y;
		y = 0;
		x++;
	}
	data->map.map_height = x;
	data->map.map_width = y_bis;
}
