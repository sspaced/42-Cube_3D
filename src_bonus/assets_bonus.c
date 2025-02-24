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

int clean_bonus_textures(t_textures *textures, t_arm *arm, void *mlx, int level)
{
	mlx_destroy_image(mlx, textures->player_dot->img.ptr);
	free(textures->player_dot);
	if (level == 1)
		return (0);
	free_annimations(&(arm->basic), 46, mlx);
	if (level == 2)
		return (0);
	free_annimations(&(arm->running), 46, mlx);
	if (level == 3)
		return (0);
	free_annimations(&(arm->finger), 46, mlx);
	if (level == 4)
		return (0);
	return (0);
}

t_list	*new_animation(void *mlx, const char *base_path,
	int frame_number, t_texture name)
{
	int		i;
	char	*path;
	char	*new_path;
	t_list	*head;
	char	*num;

	i = -1;
	path = NULL;
	head = NULL;
	while (++i < frame_number)
	{
		path = ft_strdup(base_path);
		num = ft_itoa(i);
		new_path = ft_strjoin(path, num);
		free(path);
		free(num);
		path = new_path;
		new_path = ft_strjoin(path, ".xpm");
		free(path);
		if (!add_asset_to_list(&(head), mlx, new_path, name))
			return (ft_lstclear(&(head), &destroy_asset), NULL);
	}
	ft_lstlast(head)->next = head;
	return (head);
}

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

int	add_asset_to_list(t_list **head, void *mlx, char *path, t_texture name)
{
	t_asset	*new;
	t_list	*node;

	new = new_asset(mlx, path, name);
	if (!new)
		return (0);
	node = ft_lstnew(new);
	if (!node)
	{
		free(new);
		return (ft_putstr_fd("Failed to allocate new list node\n", 2), 0);
	}
	ft_lstadd_back(head, node);
	return (1);
}
