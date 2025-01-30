/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elleroux <elleroux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:49:52 by elleroux          #+#    #+#             */
/*   Updated: 2025/01/22 19:02:16 by elleroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_asset	*new_asset(void *mlx, char *path, e_texture name)
{
	t_asset	*new;

	if (DEBUG == true)
		printf("new_asset: path=%s\n", path);
	new = ft_calloc(sizeof(t_asset), 1);
	if (!new)
		return (ft_putstr_fd("Failed to allocate new asset\n", 2), NULL);
	new->path = path;
	new->img.ptr = mlx_xpm_file_to_image(mlx, path, &(new->width), &(new->height));
	if (!new->img.ptr)
	{
		free(new);
		return (ft_putstr_fd("Failed to create X image from xpm\n", 2), NULL);
	}
	new->img.data = mlx_get_data_addr(new->img.ptr, &(new->img.bpp), &(new->img.line_len), &(new->img.endian));
	if (!new->img.data)
	{
		free(new);
		return (ft_putstr_fd("Failed to read image data\n", 2), NULL);
	}
	new->name = name;
	return (new);
}

int	add_asset_to_list(t_list **head, void *mlx, char *path, e_texture name)
{
	t_asset	*new;
	t_list	*node;

	new = new_asset(mlx, path, name);
	if (!new)
		return (0);
	node = ft_lstnew(new);
	if (!node)
	{
		free(new); // TO REPLACE WITH A DESTROY ASSET FUNCT WHEN PATH WILL BE MALLOC
		return (ft_putstr_fd("Failed to allocate new list node\n", 2), 0);
	}
	ft_lstadd_back(head, ft_lstnew(new));
	return (1);
}
