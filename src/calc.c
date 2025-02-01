/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elleroux <elleroux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:03:59 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/01 21:12:44 by elleroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void calc_ray_vector(t_data *data, int x)
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	plane_x;
	double	plane_y;
	
    // Calculate ray position and direction
    camera_x = 2 * x / (double)WIN_WIDTH - 1; // x-coordinate in camera space
    ray_dir_x = cos(RAD(data->player.direction));
    ray_dir_y = sin(RAD(data->player.direction));
    plane_x = -ray_dir_y * tan(RAD(FOV / 2));
    plane_y = ray_dir_x * tan(RAD(FOV / 2));

    data->calc.ray_vect_x = ray_dir_x + plane_x * camera_x;
    data->calc.ray_vect_y = ray_dir_y + plane_y * camera_x;
}

void calc_wall_info(t_data *data)
{
    // Calcul de la hauteur du mur
    data->calc.wall_height = (int)(WIN_HEIGHT / data->calc.perp_wall_dist);

    // Calcul des points de début et de fin du mur
    data->calc.wall_top = (WIN_HEIGHT - data->calc.wall_height) / 2;
    data->calc.wall_bottom = data->calc.wall_top + data->calc.wall_height;

    // Ajustement si le mur dépasse l'écran
    if (data->calc.wall_top < 0)
        data->calc.wall_top = 0;
    if (data->calc.wall_bottom >= WIN_HEIGHT)
        data->calc.wall_bottom = WIN_HEIGHT - 1;

    // Calcul de la position exacte du point d'impact sur le mur
    // Cela peut être utile pour le texturage
    if (data->calc.side == 0)
        data->calc.wall_x = data->player.y + data->calc.perp_wall_dist * data->calc.ray_vect_y;
    else
        data->calc.wall_x = data->player.x + data->calc.perp_wall_dist * data->calc.ray_vect_x;
    data->calc.wall_x -= floor(data->calc.wall_x);
}

int	ray_hit(t_data *data, t_fvect *side_dist, t_vect *map, t_vect step, t_fvect delta_dist)
{
        if (side_dist->x < side_dist->y)
        {
            side_dist->x += delta_dist.x;
            map->x += step.x;
            data->calc.side = 0;
        }
        else
        {
            side_dist->y += delta_dist.y;
            map->y += step.y;
            data->calc.side = 1;
        }

        if (map->x < 0 || map->y < 0 || 
            map->x >= data->map.map_width || 
            map->y >= data->map.map_height ||
            data->map.map_array[map->y][map->x] == '1')
        {
             return (1);
        }
	return (0);
}

void calc_wall_hit(t_data *data)
{
	t_vect map;
	t_fvect delta_dist;
	t_vect step;
	t_fvect side_dist;

    map.x = (int)data->player.x;
    map.y = (int)data->player.y;
    
    delta_dist.x = fabs(1 / data->calc.ray_vect_x);
    delta_dist.y = fabs(1 / data->calc.ray_vect_y);

	if (data->calc.ray_vect_x < 0)
	{
		step.x = -1;
		side_dist.x = (data->player.x - map.x) * delta_dist.x;
	}
	else
	{
		step.x = 1;
		side_dist.x = (map.x + 1.0 - data->player.x) * delta_dist.x;
	}

	if (data->calc.ray_vect_y < 0)
	{
		step.y = -1;
		side_dist.y = (data->player.y - map.y) * delta_dist.y;
	}
	else
	{
		step.y = 1;
		side_dist.y = (map.y + 1.0 - data->player.y) * delta_dist.y;
	}

	while (ray_hit(data, &side_dist, &map, step, delta_dist) == 0)
		;

	if (data->calc.side == 0)
	{
        data->calc.perp_wall_dist = (map.x - data->player.x + (1 - step.x) / 2) / data->calc.ray_vect_x;
		if (data->calc.ray_vect_x > 0)
			data->calc.wall_orientation = 'E';
		else
			data->calc.wall_orientation = 'W';
	}
	else
	{
        data->calc.perp_wall_dist = (map.y - data->player.y + (1 - step.y) / 2) / data->calc.ray_vect_y;
		if (data->calc.ray_vect_y > 0)
			data->calc.wall_orientation = 'S';
		else
			data->calc.wall_orientation = 'N';
	}
}
