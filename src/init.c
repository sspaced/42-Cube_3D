/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:27:27 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/18 15:47:13 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_colors(t_map_info *map_info)
{
	map_info->c[0] = -1;
	map_info->c[1] = -1;
	map_info->c[2] = -1;
	map_info->f[0] = -1;
	map_info->f[1] = -1;
	map_info->f[2] = -1;
}

int	init(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	init_colors(&(data->map.map_info));
	if (!(data->mlx = mlx_init()))
		return (ft_putstr_fd("Failed to init mlx\n", 2), 0);
	if (!(data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT,
				WIN_TITLE)))
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (ft_putstr_fd("Failed to open window\n", 2), 0);
	}
	if (!init_img(&(data->img), data->mlx))
	{
		mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (0);
	}
	return (1);
}

int	init_img(t_img *img, void *mlx)
{
	if (!(img->ptr = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT)))
		return (ft_putstr_fd("Failed to init new image\n", 2), 0);
	if (!(img->data = mlx_get_data_addr(img->ptr, &(img->bpp), &(img->line_len),
				&(img->endian))))
	{
		mlx_destroy_image(mlx, img->ptr);
		return (ft_putstr_fd("Failed to get new image data\n", 2), 0);
	}
	return (1);
}
