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

void	map_coord_to_pixel(t_data *data, int x, int y)
{
	float y_parcel_size = (WINDOW_WIDTH / data->map.map_width) * (y + 1);
	float x_parcel_size = (WINDOW_HEIGHT / data->map.map_height) * (x + 1);

	printf("y_parcel : %f\n", y_parcel_size);
	printf("x_parcel : %f\n", x_parcel_size);

}