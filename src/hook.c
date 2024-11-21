#include "cube.h"

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
    else if (keycode == KEY_DOWN)
        data->keys.down = 1;
    else if (keycode == KEY_LEFT)
        data->keys.left = 1;
    else if (keycode == KEY_RIGHT)
        data->keys.right = 1;
    else if (keycode == KEY_ESC)
        data->keys.esc = 1;
    return (0);
}

int key_release(int keycode, t_data *data)
{
    if (keycode == KEY_UP)
        data->keys.up = 0;
    else if (keycode == KEY_DOWN)
        data->keys.down = 0;
    else if (keycode == KEY_LEFT)
        data->keys.left = 0;
    else if (keycode == KEY_RIGHT)
        data->keys.right = 0;
    else if (keycode == KEY_ESC)
        data->keys.esc = 0;
    return (0);
}

int mouse_move(int x, int y, t_data *data)
{
	int x_mid = WINDOW_WIDTH / 2;
	int y_mid = WINDOW_HEIGHT / 2;

	mlx_mouse_move(data->mlx, data->win, x_mid, y_mid);
	if (x < x_mid)
		data->player.direction += ROTATION_SPEED * 2;
	else if (x > x_mid)
		data->player.direction -= ROTATION_SPEED * 2;
	return(0);
}

int key_hook(int keycode, t_data *data)
{
    double new_x, new_y;
    double angle = RAD(data->player.direction);
    
	if (keycode == 65307)
    {
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }

    if (keycode == KEY_UP)
    {
        new_x = data->player.x + cos(angle) * MOVE_SPEED;
        new_y = data->player.y + sin(angle) * MOVE_SPEED;
		data->player.x = new_x;
		data->player.y = new_y;
        if (!check_collision(data, new_x, new_y))
        {
        }
    }
    else if (keycode == KEY_DOWN)
    {
        new_x = data->player.x - cos(angle) * MOVE_SPEED;
        new_y = data->player.y - sin(angle) * MOVE_SPEED;
		data->player.x = new_x;
		data->player.y = new_y;
        if (!check_collision(data, new_x, new_y))
        {
        }
    }
    else if (keycode == KEY_LEFT)
    {
		data->player.direction += ROTATION_SPEED;
    }
    else if (keycode == KEY_RIGHT)
    {
		data->player.direction -= ROTATION_SPEED;
    }
    
    display_player_view(data, 0.005);
    return (0);
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

    if (data->keys.up)
    {
        new_x = data->player.x + cos(angle) * MOVE_SPEED;
        new_y = data->player.y + sin(angle) * MOVE_SPEED;
		data->player.x = new_x;
		data->player.y = new_y;
		moved = 1;
        if (!check_collision(data, new_x, new_y))
        {
        }
    }
    if (data->keys.down)
    {
        new_x = data->player.x - cos(angle) * MOVE_SPEED;
        new_y = data->player.y - sin(angle) * MOVE_SPEED;
		data->player.x = new_x;
		data->player.y = new_y;
		moved = 1;
        if (!check_collision(data, new_x, new_y))
        {
        }
    }
    if (data->keys.left)
    {
        data->player.direction += ROTATION_SPEED;
        moved = 1;
    }
    if (data->keys.right)
    {
        data->player.direction -= ROTATION_SPEED;
        moved = 1;
    }
	if (moved || BONUS)
		display_player_view(data, 0.002);

    return (0);
}

void init_keys(t_keys *keys)
{
    keys->up = 0;
    keys->down = 0;
    keys->left = 0;
    keys->right = 0;
    keys->esc = 0;
}
