/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:08:08 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/24 13:56:35 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_annimations(t_list **list, int len, void *mlx)
{
	t_list	*temp;
	int		i;

	i = 0;
	while (*list && i < len)
	{
		temp = (*list)->next;
		free(((t_asset *)(*list)->content)->path);
		mlx_destroy_image(mlx, ((t_asset *)(*list)->content)->img.ptr);
		free((*list)->content);
		free(*list);
		(*list) = temp;
		i++;
	}
}

void	destroy_asset(void *asset)
{
	free(((t_asset *)asset)->img.data);
	free(((t_asset *)asset)->img.ptr);
	free((t_asset *)asset);
}

void	free_textures_path(t_data *data)
{
	free(data->map.map_info.no);
	free(data->map.map_info.so);
	free(data->map.map_info.ea);
	free(data->map.map_info.we);
}

void	clean_mlx_textures(t_data *data)
{
	mlx_destroy_image(data->mlx, data->textures.wall_n->img.ptr);
	mlx_destroy_image(data->mlx, data->textures.wall_s->img.ptr);
	mlx_destroy_image(data->mlx, data->textures.wall_e->img.ptr);
	mlx_destroy_image(data->mlx, data->textures.wall_w->img.ptr);
	free(data->textures.wall_n);
	free(data->textures.wall_s);
	free(data->textures.wall_e);
	free(data->textures.wall_w);
}

void	clean_mlx(t_data *data)
{
	clean_mlx_textures(data);
	if (data->img.ptr)
		mlx_destroy_image(data->mlx, data->img.ptr);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}
