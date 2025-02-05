/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elleroux <elleroux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:08:08 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/01 22:15:19 by elleroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	destroy_asset(void *asset)
{
	free(((t_asset *)asset)->img.data);
	free(((t_asset *)asset)->img.ptr);
	free((t_asset *)asset);
}

void	clean_mlx(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.ptr);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	if (data->mlx)
		free(data->mlx);
}

void	clear_animations(t_arm *arm, void *mlx)
{
	destroy_animations(arm->basic, mlx);
	destroy_animations(arm->finger, mlx);
	destroy_animations(arm->running, mlx);
	destroy_animations(arm->punching, mlx);
}

void	destroy_animations(t_list *list, void *mlx)
{
	t_list	*head;
	t_list	*temp;
	t_asset	*content;

	head = list->next;
	while (list != head)
	{
		content = list->content;
		mlx_destroy_image(mlx, content->img.ptr);
		free(content);
		temp = list->next;
		free(list);
		list = temp;
	}
	content = list->content;
	mlx_destroy_image(mlx, content->img.ptr);
	free(content);
	temp = list->next;
	free(list);
}
