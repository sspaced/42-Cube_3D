/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:15 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/24 13:59:55 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	setup_hooks(t_data *data)
{
	mlx_hook(data->win, KEY_PRESS, KEY_PRESS_MASK, key_press, data);
	mlx_hook(data->win, KEY_RELEASE, KEY_RELEASE_MASK, key_release, data);
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

int	init_textures(t_data *data)
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

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;
	if (!init(&data))
		return (1);
	if (!parser(argv, &data, argc))
		return (1);
	set_map_height_width(&data);
	set_player_pos_dir(&data);
	setup_hooks(&data);
	if (!init_textures(&data))
		return (1);
	if (BONUS == true && (!setup_bonus_textures(&(data.textures), &(data.arm),
				data.mlx)))
		return (1);
	display_player_view(&data);
	free_textures_path(&data);
	mlx_loop(data.mlx);
	return (1);
}
