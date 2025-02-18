/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:15 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/18 15:56:02 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	setup_map(t_map *map, char *path)
{
	map->map_array = read_map_file(path);
	if (!map->map_array)
		return (ft_putstr_fd("Failed to read map file\n", 2), 0);
	set_map_height_width(map);
	return (1);
}

int	setup_hooks(t_data *data)
{
	mlx_hook(data->win, KEY_PRESS, KEY_PRESS_MASK, key_press, data);      
		// KeyPress
	mlx_hook(data->win, KEY_RELEASE, KEY_RELEASE_MASK, key_release, data);
		// KeyRelease
	mlx_hook(data->win, DESTROY_NOTIFY, 0, close_window, data);
	mlx_loop_hook(data->mlx, handle_movement, data);
	if (BONUS == true)
	{
		mlx_hook(data->win, MOTION_NOTIFY, POINTER_MOTION_MASK, mouse_move,
			data);
		mlx_mouse_hide(data->mlx, data->win);
		mlx_hook(data->win, BUTTON_PRESS, BUTTON_PRESS_MASK, mouse_click, data);
		mlx_hook(data->win, BUTTON_RELEASE, BUTTON_RELEASE_MASK, mouse_release,
			data);
	}
	return (1);
}

int	setup_bonus_textures(t_textures *textures, t_arm *arm, void *mlx)
{
	textures->player_dot = new_asset(mlx,
			"assets/img/player_dot/player_dot.xpm", PLAYER_DOT);
	if (!textures->player_dot)
		return (0);
	arm->basic = new_animation(mlx, "assets/img/arm/", 46, ARM_STATIC);
	arm->running = new_animation(mlx, "assets/img/arm_running_fast/", 21,
			ARM_RUNNING);
	arm->finger = new_animation(mlx, "assets/img/arm_finger/", 17, ARM_FINGER);
	arm->punching = new_animation(mlx, "assets/img/arm_punching/", 33,
			ARM_PUNCHING);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	// Init all data
	if (!init(&data))
		return (1);
	// Creating map object
	if (!parser(argv, &data))
		return (1);
	// Set player in map
	set_player_pos_dir(&data);
	// Setting mlx hook to catch X event
	setup_hooks(&data);
	// Setting texture (will be done via parsing later)
	data.textures.wall_n = new_asset(data.mlx, "assets/img/text_n/text_n.xpm",
			WALL_N);
	if (!data.textures.wall_n)
		return (1);
	data.textures.wall_s = new_asset(data.mlx, "assets/img/text_s/text_s.xpm",
			WALL_S);
	if (!data.textures.wall_s)
		return (1);
	data.textures.wall_e = new_asset(data.mlx, "assets/img/text_e/text_e.xpm",
			WALL_E);
	if (!data.textures.wall_e)
		return (1);
	data.textures.wall_w = new_asset(data.mlx, "assets/img/text_w/text_w.xpm",
			WALL_W);
	if (!data.textures.wall_w)
		return (1);
	if (BONUS == true && (!setup_bonus_textures(&(data.textures), &(data.arm),
				data.mlx)))
		return (1);
	display_player_view(&data);
	mlx_loop(data.mlx);
	free_map_error(data.map.map_array);
	clear_animations(&(data.arm), &(data.mlx));
	// ft_lstclear(&(data.arm.finger), &destroy_asset);
	// ft_lstclear(&(data.arm.basic), &destroy_asset);
	// ft_lstclear(&(data.arm.running), &destroy_asset);
	// ft_lstclear(&(data.arm.punching), &destroy_asset);
	// free(&(data.arm.punching));
	// free(&(data.arm.running));
	// free(&(data.arm.finger));
	// free(&(data.arm.basic));
	clean_mlx(&(data));
	return (1);
}
