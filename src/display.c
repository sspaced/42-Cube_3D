#include "cube.h"

void    pixel_to_img(t_data *data, int x, int y, int color)
{
    char    *pixel;
    int     i;

    if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
        return;
    i = data->line_length * y + x * (data->bits_per_pixel / 8);
    pixel = data->addr + i;
    *(unsigned int*)pixel = color;
}

// void	display_player_view(t_data *data, float view_angle)
// {
// 	float	x = (WINDOW_WIDTH / data->map.map_width) * (data->player.x + 1);
// 	float	y = (WINDOW_HEIGHT / data->map.map_height) * (data->player.y + 1);
// 	printf("x = %f, y = %f\n", x, y);
// 	pixel_to_img(data, 432, 640, 0x00FF0000);
// 	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

// }


// Fonction pour vérifier les collisions
int check_collision(t_data *data, double new_x, double new_y)
{
    int map_x = (int)new_x;
    int map_y = (int)new_y;
    
    if (map_x < 0 || map_y < 0 || 
        map_x >= data->map.map_width || 
        map_y >= data->map.map_height ||
        data->map.map_array[map_y][map_x] == '1')
        return 1;
    return 0;
}

void display_player_view(t_data *data, double step)
{
    int x;
	int y;

	x = 0;
    while(x < WINDOW_WIDTH)
    {
		calc_ray_vector(data, x);
		calc_wall_hit(data, step);
		calc_wall_info(data);
		y = 0;
		while (y < data->calc.wall_top)
			pixel_to_img(data, x, y++, CEILING);
		y = data->calc.wall_top;
		while (y < data->calc.wall_bottom)
			pixel_to_img(data, x, y++, WALL_COLOR);
		y = data->calc.wall_bottom;
		while (y < WINDOW_HEIGHT)
			pixel_to_img(data, x, y++, FLOOR);
		x++;
    }

    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int get_player_angle(char direction)
{
    switch (direction)
    {
        case 'N': return 270;
        case 'S': return 90;
        case 'E': return 0;
        case 'W': return 180;
        default: return 0;
    }
}