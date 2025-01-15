#include "cub.h"

// void	calc_ray_vector(t_data *data, int x)
// {
// 	data->calc.ray_angle = RAD(data->player.direction) + 
//                    RAD(FOV / 2.0) - ((double)x / WINDOW_WIDTH) * RAD(FOV);
//     data->calc.ray_vect_x = cos(data->calc.ray_angle);
//     data->calc.ray_vect_y = sin(data->calc.ray_angle);
// }

void calc_ray_vector(t_data *data, int x)
{
    // Calculate ray position and direction
    double camera_x = 2 * x / (double)WINDOW_WIDTH - 1; // x-coordinate in camera space
    double ray_dir_x = cos(RAD(data->player.direction));
    double ray_dir_y = sin(RAD(data->player.direction));
    double plane_x = -ray_dir_y * tan(RAD(FOV / 2));
    double plane_y = ray_dir_x * tan(RAD(FOV / 2));

    data->calc.ray_vect_x = ray_dir_x + plane_x * camera_x;
    data->calc.ray_vect_y = ray_dir_y + plane_y * camera_x;
}

// void calc_wall_info(t_data *data)
// {
// 	data->calc.wall_x = data->calc.wall_x - data->player.x;
// 	data->calc.wall_y = data->calc.wall_y - data->player.y;
//     data->calc.wall_dist = sqrt(data->calc.wall_x * data->calc.wall_x + data->calc.wall_y * data->calc.wall_y);
//     data->calc.wall_dist *= cos(data->calc.ray_angle - RAD(data->player.direction));
// 	data->calc.wall_height = (int)(WINDOW_HEIGHT / data->calc.wall_dist);
//     if (data->calc.wall_height > WINDOW_HEIGHT)
// 		data->calc.wall_height = WINDOW_HEIGHT;
// 	data->calc.wall_top = (WINDOW_HEIGHT - data->calc.wall_height) / 2;
//     data->calc.wall_bottom = data->calc.wall_top + data->calc.wall_height;
// }


void calc_wall_info(t_data *data)
{
    // Calcul de la hauteur du mur
    data->calc.wall_height = (int)(WINDOW_HEIGHT / data->calc.perp_wall_dist);

    // Calcul des points de début et de fin du mur
    data->calc.wall_top = (WINDOW_HEIGHT - data->calc.wall_height) / 2;
    data->calc.wall_bottom = data->calc.wall_top + data->calc.wall_height;

    // Ajustement si le mur dépasse l'écran
    if (data->calc.wall_top < 0)
        data->calc.wall_top = 0;
    if (data->calc.wall_bottom >= WINDOW_HEIGHT)
        data->calc.wall_bottom = WINDOW_HEIGHT - 1;

    // Calcul de la position exacte du point d'impact sur le mur
    // Cela peut être utile pour le texturage
    if (data->calc.side == 0)
        data->calc.wall_x = data->player.y + data->calc.perp_wall_dist * data->calc.ray_vect_y;
    else
        data->calc.wall_x = data->player.x + data->calc.perp_wall_dist * data->calc.ray_vect_x;
    data->calc.wall_x -= floor(data->calc.wall_x);
}

void calc_wall_hit(t_data *data)
{
    int map_x = (int)data->player.x;
    int map_y = (int)data->player.y;
    
    double delta_dist_x = fabs(1 / data->calc.ray_vect_x);
    double delta_dist_y = fabs(1 / data->calc.ray_vect_y);

    int step_x = (data->calc.ray_vect_x < 0) ? -1 : 1;
    int step_y = (data->calc.ray_vect_y < 0) ? -1 : 1;

    double side_dist_x = (data->calc.ray_vect_x < 0) ? 
        (data->player.x - map_x) * delta_dist_x : 
        (map_x + 1.0 - data->player.x) * delta_dist_x;
    double side_dist_y = (data->calc.ray_vect_y < 0) ? 
        (data->player.y - map_y) * delta_dist_y : 
        (map_y + 1.0 - data->player.y) * delta_dist_y;

    int hit = 0;
    int side; // 0 for x-side, 1 for y-side

    while (hit == 0)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }

        if (map_x < 0 || map_y < 0 || 
            map_x >= data->map.map_width || 
            map_y >= data->map.map_height ||
            data->map.map_array[map_y][map_x] == '1')
        {
            hit = 1;
        }
    }

    // if (side == 0)
    //     data->calc.perp_wall_dist = (map_x - data->player.x + (1 - step_x) / 2) / data->calc.ray_vect_x;
    // else
    //     data->calc.perp_wall_dist = (map_y - data->player.y + (1 - step_y) / 2) / data->calc.ray_vect_y;

	if (side == 0)
        data->calc.perp_wall_dist = (map_x - data->player.x + (1 - step_x) / 2) / data->calc.ray_vect_x;
	else
        data->calc.perp_wall_dist = (map_y - data->player.y + (1 - step_y) / 2) / data->calc.ray_vect_y;

	if (side == 0)
        data->calc.wall_orientation = (data->calc.ray_vect_x > 0) ? 'E' : 'W';
	else
        data->calc.wall_orientation = (data->calc.ray_vect_y > 0) ? 'S' : 'N';
    // data->calc.wall_x = data->player.x + data->calc.perp_wall_dist * data->calc.ray_vect_x;
    // data->calc.wall_y = data->player.y + data->calc.perp_wall_dist * data->calc.ray_vect_y;
}

// void calc_wall_hit(t_data *data)
// {
// 	double	step;
// 
// 	step = 0.005;
// 	data->calc.wall_x = data->player.x;
//     data->calc.wall_y = data->player.y;
// 	while (1)
//     {
// 		data->calc.wall_x += data->calc.ray_vect_x * step;
//         data->calc.wall_y += data->calc.ray_vect_y * step;
//         if ((int)data->calc.wall_x < 0 || (int)data->calc.wall_y < 0 ||
// 				(int)data->calc.wall_x >= data->map.map_width || 
//             	(int)data->calc.wall_y >= data->map.map_height ||
//             	data->map.map_array[(int)data->calc.wall_y][(int)data->calc.wall_x] == '1')
// 			break;
//     }
// }
