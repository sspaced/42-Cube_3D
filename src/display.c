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

unsigned int	get_pixel_img(t_asset *img, int x, int y)
{
	return (*(unsigned int *)((img->data + (y * img->line_len) + (x * img->bpp / 8))));
}

void	put_pixel_img(t_data *img, int x, int y, int color)
{
	char	*dst;

	if (x > 1920)
		x = x % 1920;
	if (color == (int)0xFF000000)
		return ;
	if (x >= 0 && y >= 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT) {
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *) dst = color;
	}
}

void	put_img_to_img(t_data *dst, t_asset *src, int x, int y)
{
	static int i = {0};
	int j;

	i++;
	while(i % 1920 != 0)
	{
		j = 0;
		while (j < src->height)
		{
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
	if (i == 86400) // 1920 * 45 -> nombre de frames dans l'animation
		i = 0;
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
		//y = data->calc.wall_top;
		// printf("angle : %d\n", data->player.direction);
		while (y < data->calc.wall_bottom)
		{
			//if (data->player.direction % 360 - 270 > 0);
			pixel_to_img(data, x, y++, WALL_COLOR);
		}
		//y = data->calc.wall_bottom;
		while (y < WINDOW_HEIGHT)
			pixel_to_img(data, x, y++, FLOOR);
		x++;
    }

	put_img_to_img(data, data->asset, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	// mlx_put_image_to_window(data->mlx, data->win, data->asset->img_ptr, 0, 0);
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
