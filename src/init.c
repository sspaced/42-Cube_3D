/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:27:27 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/24 15:46:25 by lben-adi         ###   ########.fr       */
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
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (ft_putstr_fd("Failed to init mlx\n", 2), 0);
	data->mlx = mlx_ptr;
	win_ptr = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!win_ptr)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (ft_putstr_fd("Failed to open window\n", 2), 0);
	}
	data->win = win_ptr;
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
	void	*img_ptr;
	char	*img_data;

	img_ptr = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!img_ptr)
		return (ft_putstr_fd("Failed to init new image\n", 2), 0);
	img->ptr = img_ptr;
	img_data = mlx_get_data_addr(img->ptr, &(img->bpp), &(img->line_len),
			&(img->endian));
	if (!img_data)
	{
		mlx_destroy_image(mlx, img->ptr);
		return (ft_putstr_fd("Failed to get new image data\n", 2), 0);
	}
	img->data = img_data;
	return (1);
}
