/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 20:03:59 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/24 13:53:55 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	calc_ray_vector(t_data *data, int x)
{
	double	camera_x;
	t_fvect	ray_dir;
	t_fvect	plane;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray_dir.x = cos(RAD(data->player.direction));
	ray_dir.y = sin(RAD(data->player.direction));
	plane.x = -ray_dir.y * tan(RAD(FOV / 2));
	plane.y = ray_dir.x * tan(RAD(FOV / 2));
	data->calc.ray_vect_x = ray_dir.x + plane.x * camera_x;
	data->calc.ray_vect_y = ray_dir.y + plane.y * camera_x;
}

void	calc_wall_info(t_data *data)
{
	if (data->calc.perp_wall_dist <= 0.0001)
		data->calc.perp_wall_dist = 0.0001;
	data->calc.wall_height = (int)(WIN_HEIGHT / data->calc.perp_wall_dist);
	if (data->calc.wall_height > WIN_HEIGHT * 10)
		data->calc.wall_height = WIN_HEIGHT * 10;
	data->calc.wall_top = (WIN_HEIGHT - data->calc.wall_height) / 2;
	data->calc.wall_bottom = data->calc.wall_top + data->calc.wall_height;
	if (data->calc.wall_top < 0)
		data->calc.wall_top = 0;
	if (data->calc.wall_bottom >= WIN_HEIGHT)
		data->calc.wall_bottom = WIN_HEIGHT - 1;
	if (data->calc.side == 0)
		data->calc.wall_x = data->player.y + data->calc.perp_wall_dist
			* data->calc.ray_vect_y;
	else
		data->calc.wall_x = data->player.x + data->calc.perp_wall_dist
			* data->calc.ray_vect_x;
	data->calc.wall_x -= floor(data->calc.wall_x);
}
