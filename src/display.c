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

void display_player_view(t_data *data, double move_speed)
{
    mlx_clear_window(data->mlx, data->win);
    
    double ray_angle;
    double ray_x, ray_y;
    double ray_cos, ray_sin;
    double dist_to_wall;
    int column;
    int wall_height;
    
    for (column = 0; column < WINDOW_WIDTH; column++)
    {
        ray_angle = RAD(data->player.direction) + 
                   RAD(FOV / 2.0) - ((double)column / WINDOW_WIDTH) * RAD(FOV);
        
        ray_cos = cos(ray_angle);
        ray_sin = sin(ray_angle);
        
        ray_x = data->player.x;
        ray_y = data->player.y;
        
        while (1)
        {
            ray_x += ray_cos * move_speed;
            ray_y += ray_sin * move_speed;
            
            int map_x = (int)ray_x;
            int map_y = (int)ray_y;
            
            if (map_x < 0 || map_y < 0 || 
                map_x >= data->map.map_width || 
                map_y >= data->map.map_height ||
                data->map.map_array[map_y][map_x] == '1')
                break;
        }
        
        double dx = ray_x - data->player.x;
        double dy = ray_y - data->player.y;
        dist_to_wall = sqrt(dx * dx + dy * dy);
        
        dist_to_wall *= cos(ray_angle - RAD(data->player.direction));
        
        wall_height = (int)(WINDOW_HEIGHT / dist_to_wall);
        if (wall_height > WINDOW_HEIGHT)
            wall_height = WINDOW_HEIGHT;
            
        int wall_top = (WINDOW_HEIGHT - wall_height) / 2;
        int wall_bottom = wall_top + wall_height;
        
        for (int y = 0; y < wall_top; y++)
            pixel_to_img(data, column, y, 0x444444);
            
        for (int y = wall_top; y < wall_bottom; y++)
        {
            int color = 0xFFFFFF;
            int shade = (int)(255.0 / (1.0 + dist_to_wall * 0.1));
            color = (shade << 16) | (shade << 8) | shade;
            pixel_to_img(data, column, y, color);
        }
        
        for (int y = wall_bottom; y < WINDOW_HEIGHT; y++)
            pixel_to_img(data, column, y, 0x666666);
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