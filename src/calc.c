/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:03:59 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/24 13:53:49 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	ray_hit(t_data *data, t_ray_data ray)
{
	if (ray.side_dist->x < ray.side_dist->y)
	{
		ray.side_dist->x += ray.delta_dist.x;
		ray.map->x += ray.step.x;
		data->calc.side = 0;
	}
	else
	{
		ray.side_dist->y += ray.delta_dist.y;
		ray.map->y += ray.step.y;
		data->calc.side = 1;
	}
	if (ray.map->x < 0 || ray.map->y < 0 || ray.map->x >= data->map.map_width
		|| ray.map->y >= data->map.map_height
		|| data->map.map_array[ray.map->y][ray.map->x] == '1')
		return (1);
	return (0);
}

static void	init_step_and_side_dist(t_data *data, t_vect *map,
	t_fvect *side_dist, t_ray_data *ray)
{
	if (data->calc.ray_vect_x < 0)
	{
		ray->step.x = -1;
		side_dist->x = (data->player.x - map->x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		side_dist->x = (map->x + 1.0 - data->player.x) * ray->delta_dist.x;
	}
	if (data->calc.ray_vect_y < 0)
	{
		ray->step.y = -1;
		side_dist->y = (data->player.y - map->y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		side_dist->y = (map->y + 1.0 - data->player.y) * ray->delta_dist.y;
	}
}

static void	set_wall_orientation(t_data *data, t_vect map, t_vect step)
{
	if (data->calc.side == 0)
	{
		data->calc.perp_wall_dist = (map.x - data->player.x + (1 - step.x) / 2)
			/ data->calc.ray_vect_x;
		if (data->calc.ray_vect_x > 0)
			data->calc.wall_orientation = 'E';
		else
			data->calc.wall_orientation = 'W';
	}
	else
	{
		data->calc.perp_wall_dist = (map.y - data->player.y + (1 - step.y) / 2)
			/ data->calc.ray_vect_y;
		if (data->calc.ray_vect_y > 0)
			data->calc.wall_orientation = 'S';
		else
			data->calc.wall_orientation = 'N';
	}
}

void	calc_wall_hit(t_data *data)
{
	t_vect		map;
	t_fvect		side_dist;
	t_ray_data	ray;

	map.x = (int)data->player.x;
	map.y = (int)data->player.y;
	ray.delta_dist.x = fabs(1 / data->calc.ray_vect_x);
	ray.delta_dist.y = fabs(1 / data->calc.ray_vect_y);
	ray.map = &map;
	ray.side_dist = &side_dist;
	init_step_and_side_dist(data, &map, &side_dist, &ray);
	while (ray_hit(data, ray) == 0)
		;
	set_wall_orientation(data, map, ray.step);
}
