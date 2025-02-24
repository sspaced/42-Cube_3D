/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assets.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:49:52 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/24 14:26:46 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_asset	*new_asset(void *mlx, char *path, t_texture name)
{
	t_asset	*new;

	if (DEBUG == true)
		printf("new_asset: path=%s\n", path);
	new = ft_calloc(sizeof(t_asset), 1);
	if (!new)
		return (ft_putstr_fd("Failed to allocate new asset\n", 2), NULL);
	new->path = path;
	new->img.ptr = mlx_xpm_file_to_image(mlx, path,
			&(new->width), &(new->height));
	if (!new->img.ptr)
	{
		free(new);
		return (ft_putstr_fd("Failed to create X image from xpm\n", 2), NULL);
	}
	new->img.data = mlx_get_data_addr(new->img.ptr, &(new->img.bpp),
			&(new->img.line_len), &(new->img.endian));
	if (!new->img.data)
	{
		mlx_destroy_image(mlx, new->img.ptr);
		free(new);
		return (ft_putstr_fd("Failed to read image data\n", 2), NULL);
	}
	new->name = name;
	return (new);
}
