#include "cub.h"

void	set_map_height_width(t_map *map)
{
	int x;
	int y;
	int y_bis;

	if (!map->map_array)
		return ;
	x = 0;
	y = 0;
	y_bis = 0;
	while (map->map_array[x])
	{
		while (map->map_array[x][y])
			y++;
		y_bis = y;
		y = 0;
		x++;
	}
	map->map_height = x;
	map->map_width = y_bis;
}

void	map_coord_to_pixel(t_data *data, int x, int y)
{
	float y_parcel_size = (WIN_WIDTH / data->map.map_width) * (y + 1);
	float x_parcel_size = (WIN_HEIGHT / data->map.map_height) * (x + 1);

	printf("y_parcel : %f\n", y_parcel_size);
	printf("x_parcel : %f\n", x_parcel_size);

}
