#include "cube.h"

int key_hook(int keycode, t_data *data)
{
    if (keycode == 65307)
    {
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
    return (0);
}

int	close_window(t_data *data)
{
    mlx_destroy_window(data->mlx, data->win);
    exit(0);
    return (0);
}