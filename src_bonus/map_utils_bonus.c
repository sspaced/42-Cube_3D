/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:49:52 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/19 17:40:08 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_map_height_width(t_data *data)
{
	int	x;
	int	y;
	int	y_bis;

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
	float	y_parcel_size;
	float	x_parcel_size;

	y_parcel_size = (WIN_WIDTH / data->map.map_width) * (y + 1);
	x_parcel_size = (WIN_HEIGHT / data->map.map_height) * (x + 1);
	printf("y_parcel : %f\n", y_parcel_size);
	printf("x_parcel : %f\n", x_parcel_size);
}
