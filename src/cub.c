/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:15 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/24 15:42:16 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	setup_hooks(t_data *data)
{
	mlx_hook(data->win, KEY_PRESS, 1L << 0, key_press, data);
	mlx_hook(data->win, KEY_RELEASE, 1L << 1, key_release, data);
	mlx_hook(data->win, DESTROY_NOTIFY, 0, close_window, data);
	mlx_loop_hook(data->mlx, handle_movement, data);
	return (1);
}

int	init_wall_textures(t_data *data)
{
	data->textures.wall_n = new_asset(data->mlx, data->map.map_info.no, WALL_N);
	if (!data->textures.wall_n)
		return (0);
	data->textures.wall_s = new_asset(data->mlx, data->map.map_info.so, WALL_S);
	if (!data->textures.wall_s)
		return (0);
	data->textures.wall_e = new_asset(data->mlx, data->map.map_info.ea, WALL_E);
	if (!data->textures.wall_e)
		return (0);
	data->textures.wall_w = new_asset(data->mlx, data->map.map_info.we, WALL_W);
	if (!data->textures.wall_w)
		return (0);
	return (1);
}

void	setup_error(t_data *data, int level)
{
	clear_array(data->map.map_array);
	free_textures_path(data);
	if (level == 1)
		exit (1);
	mlx_destroy_image(data->mlx, data->img.ptr);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	init_colors(&(data.map.map_info));
	if (!parser(argv, &data, argc))
		setup_error(&data, 1);
	if (!init(&data))
		setup_error(&data, 1);
	set_map_height_width(&data);
	set_player_pos_dir(&data);
	setup_hooks(&data);
	if (!init_wall_textures(&data))
		setup_error(&data, 2);
	display_player_view(&data);
	free_textures_path(&data);
	mlx_loop(data.mlx);
	return (0);
}
