/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elleroux <elleroux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:49:05 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/03 15:55:34 by elleroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	mouse_click(int keycode, int x, int y, t_data *data)
{
	(void)y;
	(void)x;
	if (keycode == RBUTTON)
		data->keys.m_right = 1;
	if (keycode == LBUTTON)
		data->keys.m_left = 1;
	return (0);
}

int	mouse_release(int keycode, int x, int y, t_data *data)
{
	(void)y;
	(void)x;
	if (keycode == RBUTTON)
		data->keys.m_right = 0;
	if (keycode == LBUTTON)
		data->keys.m_left = 0;
	return (0);
}

int	mouse_move(int x, int y, t_data *data)
{
	int	x_mid;
	int	y_mid;

	(void)y;
	x_mid = WIN_WIDTH / 2;
	y_mid = WIN_HEIGHT / 2;
	mlx_mouse_move(data->mlx, data->win, x_mid, y_mid);
	if (x < x_mid)
		data->player.direction -= ROTATION_SPEED * 2;
	else if (x > x_mid)
		data->player.direction += ROTATION_SPEED * 2;
	return (0);
}
