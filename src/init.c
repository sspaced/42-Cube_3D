/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elleroux <elleroux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:27:27 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/03 16:28:55 by elleroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int init(t_data *data)
{
	// Set data structure to 0
	ft_bzero(data, sizeof(t_data));
	// Init mlx
	if (!(data->mlx = mlx_init()))
		return (ft_putstr_fd("Failed to init mlx\n", 2), 0);
	// Open new window
    if (!(data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE)))
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
    if (!(img->data = mlx_get_data_addr(img->ptr, &(img->bpp),
		&(img->line_len), &(img->endian))))
	{
		mlx_destroy_image(mlx,img->ptr);
		return (ft_putstr_fd("Failed to get new image data\n", 2), 0);
	}
	return (1);
}
