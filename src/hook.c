/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:51:48 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/24 13:56:21 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <X11/keysym.h>

int	close_window(t_data *data)
{
	free_map_error(data->map.map_array);
	clean_mlx(data);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_LEFT)
		data->keys.left = 1;
	if (keycode == KEY_RIGHT)
		data->keys.right = 1;
	if (keycode == XK_w)
		data->keys.w = 1;
	if (keycode == XK_a)
		data->keys.a = 1;
	if (keycode == XK_s)
		data->keys.s = 1;
	if (keycode == XK_d)
		data->keys.d = 1;
	if (keycode == KEY_ESC)
		data->keys.esc = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == XK_w)
		data->keys.w = 0;
	if (keycode == XK_a)
		data->keys.a = 0;
	if (keycode == XK_s)
		data->keys.s = 0;
	if (keycode == XK_d)
		data->keys.d = 0;
	if (keycode == KEY_LEFT)
		data->keys.left = 0;
	if (keycode == KEY_RIGHT)
		data->keys.right = 0;
	if (keycode == KEY_ESC)
		data->keys.esc = 0;
	return (0);
}

int	handle_movement(t_data *data)
{
	double	angle;

	angle = rad(data->player.direction);
	if (data->keys.esc)
		close_window(data);
	if (data->keys.w)
		move_foward(&(data->player), &(data->map), angle);
	if (data->keys.a)
		move_left(&(data->player), &(data->map), angle);
	if (data->keys.s)
		move_backward(&(data->player), &(data->map), angle);
	if (data->keys.d)
		move_right(&(data->player), &(data->map), angle);
	if (data->keys.left)
		data->player.direction -= ROTATION_SPEED * 2;
	if (data->keys.right)
		data->player.direction += ROTATION_SPEED * 2;
	display_player_view(data);
	return (0);
}
