#include "cub.h"

void	calc_ray_vector(t_data *data, int x)
{
	data->calc.ray_angle = RAD(data->player.direction) + 
                   RAD(FOV / 2.0) - ((double)x / WINDOW_WIDTH) * RAD(FOV);
    data->calc.ray_vect_x = cos(data->calc.ray_angle);
    data->calc.ray_vect_y = sin(data->calc.ray_angle);
}

void calc_wall_info(t_data *data)
{
	data->calc.wall_x = data->calc.wall_x - data->player.x;
	data->calc.wall_y = data->calc.wall_y - data->player.y;
    data->calc.wall_dist = sqrt(data->calc.wall_x * data->calc.wall_x + data->calc.wall_y * data->calc.wall_y);
    data->calc.wall_dist *= cos(data->calc.ray_angle - RAD(data->player.direction));
	data->calc.wall_height = (int)(WINDOW_HEIGHT / data->calc.wall_dist);
    if (data->calc.wall_height > WINDOW_HEIGHT)
		data->calc.wall_height = WINDOW_HEIGHT;
	data->calc.wall_top = (WINDOW_HEIGHT - data->calc.wall_height) / 2;
    data->calc.wall_bottom = data->calc.wall_top + data->calc.wall_height;
}

void calc_wall_hit(t_data *data, double step)
{
	data->calc.wall_x = data->player.x;
    data->calc.wall_y = data->player.y;
	while (1)
    {
		data->calc.wall_x += data->calc.ray_vect_x * step;
        data->calc.wall_y += data->calc.ray_vect_y * step;
        if ((int)data->calc.wall_x < 0 || (int)data->calc.wall_y < 0 ||
				(int)data->calc.wall_x >= data->map.map_width || 
            	(int)data->calc.wall_y >= data->map.map_height ||
            	data->map.map_array[(int)data->calc.wall_y][(int)data->calc.wall_x] == '1')
			break;
    }
}
