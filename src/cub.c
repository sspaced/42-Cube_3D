/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elleroux <elleroux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:15 by elleroux          #+#    #+#             */
/*   Updated: 2024/11/28 14:16:18 by elleroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int argc, char **argv)
{
	t_data  data;
	if (argc != 2)
		return (ft_putstr_fd("Invalid argument\n", 2), 0);
	if (!check_file_path(argv[1]))
		return (ft_putstr_fd("Invalid path\n", 2), 0);
	init_data(&data);
	init_keys(&data.keys);
	data.mlx = mlx_init();
    if (!data.mlx)
		return (1);
    data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    if (!data.win)
		return (free(data.mlx), 1);
	init_img(&data);
	data.map.map_array = read_map_file(argv[1]);
	set_map_height_width(&data);
	set_player_pos_dir(&data);

	// printf("height = %d width = %d\n", data.map.map_height, data.map.map_width);
	// printf("x = %f y = %f d = %c\n", data.player.x, data.player.y, data.player.direction);

	mlx_hook(data.win, KEY_PRESS, KEY_PRESS_MASK, key_press, &data);    // KeyPress
    mlx_hook(data.win, KEY_RELEASE, KEY_RELEASE_MASK, key_release, &data);  // KeyRelease
	if (BONUS)
	{
		mlx_hook(data.win, MOTION_NOTIFY, POINTER_MOTION_MASK, mouse_move, &data);
		mlx_mouse_hide(data.mlx, data.win);
	}
    mlx_hook(data.win, DESTROY_NOTIFY, 0, close_window, &data);
    mlx_loop_hook(data.mlx, handle_movement, &data);

	t_asset arm;
	t_asset player_dot;
	
	ft_bzero(&arm, sizeof(t_asset));
	arm.path = "assets/img/arm/arm-void.xpm";
	arm.img_ptr = mlx_xpm_file_to_image(data.mlx, arm.path, &(arm.width), &(arm.height));
	if (arm.img_ptr == NULL)
		printf("Failed to open %s.\n", arm.path);
	arm.data = mlx_get_data_addr(arm.img_ptr, &(arm.bpp), &(arm.line_len), &(arm.endian));
	data.arm = &arm;

	ft_bzero(&player_dot, sizeof(t_asset));
	player_dot.path = "assets/img/player_dot/player_dot.xpm";
	player_dot.img_ptr = mlx_xpm_file_to_image(data.mlx, player_dot.path, &(player_dot.width), &(player_dot.height));
	if (player_dot.img_ptr == NULL)
		printf("Failed to open %s.\n", player_dot.path);
	player_dot.data = mlx_get_data_addr(player_dot.img_ptr, &(player_dot.bpp), &(player_dot.line_len), &(player_dot.endian));
	data.player_dot = &player_dot;

	display_player_view(&data, 0.005);
    mlx_loop(data.mlx);
	free_map_error(data.map.map_array);
	return (1);
}


