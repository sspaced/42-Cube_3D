#include "cub.h"
#include <X11/keysym.h>

int	close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
    return (0);
}

int key_press(int keycode, t_data *data)
{
    if (keycode == KEY_UP)
        data->keys.up = 1;
    if (keycode == KEY_DOWN)
        data->keys.down = 1;
    if (keycode == XK_w)
        data->keys.w = 1;
    if (keycode == XK_a)
        data->keys.a = 1;
    if (keycode == XK_s)
        data->keys.s = 1;
    if (keycode == XK_d)
		data->keys.d = 1;
    if (keycode == KEY_LEFT)
		data->keys.left = 1;
    if (keycode == KEY_RIGHT)
		data->keys.right = 1;
	if (keycode == KEY_ESC)
		data->keys.esc = 1;
    return (0);
}

int mouse_click(int keycode, int x, int y, t_data *data)
{
	(void)y;
	(void)x;
	if (keycode == RBUTTON)
		data->keys.m_right = 1;
	if (keycode == LBUTTON)
		data->keys.m_left = 1;
	return (0);
}

int mouse_release(int keycode, int x, int y, t_data *data)
{
	(void)y;
	(void)x;
	if (keycode == RBUTTON)
		data->keys.m_right = 0;
	if (keycode == LBUTTON)
		data->keys.m_left = 0;
	return (0);
}

int key_release(int keycode, t_data *data)
{
    if (keycode == KEY_UP)
        data->keys.up = 0;
    if (keycode == KEY_DOWN)
        data->keys.down = 0;
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

int mouse_move(int x, int y, t_data *data)
{
	int x_mid = WIN_WIDTH / 2;
	int y_mid = WIN_HEIGHT / 2;
	(void)y;

	mlx_mouse_move(data->mlx, data->win, x_mid, y_mid);
	if (x < x_mid)
		data->player.direction -= ROTATION_SPEED * 2;
	else if (x > x_mid)
		data->player.direction += ROTATION_SPEED * 2;
	return(0);
}

int handle_movement(t_data *data)
{
    int moved = 0;
    double new_x, new_y;
    double angle = RAD(data->player.direction);

    if (data->keys.esc)
    {
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
    if (data->keys.up || data->keys.w)
    {
        new_x = data->player.x + cos(angle) * MOVE_SPEED;
        new_y = data->player.y + sin(angle) * MOVE_SPEED;
        if (!check_collision(data, new_x, new_y))
        {
			data->player.x = new_x;
			data->player.y = new_y;
			moved = 1;
        }
    }
	if (data->keys.a)
	{
		new_x = data->player.x + sin(angle) * MOVE_SPEED;
		new_y = data->player.y - cos(angle) * MOVE_SPEED;
		if (!check_collision(data, new_x, new_y))
		{
			data->player.x = new_x;
			data->player.y = new_y;
			moved = 1;
		}
	}
    if (data->keys.down || data->keys.s)
    {
        new_x = data->player.x - cos(angle) * MOVE_SPEED;
        new_y = data->player.y - sin(angle) * MOVE_SPEED;
        if (!check_collision(data, new_x, new_y))
        {
			data->player.x = new_x;
			data->player.y = new_y;
			moved = 1;
        }
    }
	if (data->keys.d)
	{
		new_x = data->player.x - sin(angle) * MOVE_SPEED;
		new_y = data->player.y + cos(angle) * MOVE_SPEED;
		if (!check_collision(data, new_x, new_y))
		{
			data->player.x = new_x;
			data->player.y = new_y;
			moved = 1;
		}
	}
    if (data->keys.left)
    {
        data->player.direction -= ROTATION_SPEED * 2;
        moved = 1;
    }
    if (data->keys.right)
    {
        data->player.direction += ROTATION_SPEED;
        moved = 1;
    }
	if (moved || BONUS)
	{
		display_player_view(data);
	}

    return (0);
}
