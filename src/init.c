#include "cub.h"

// static	void init_map(t_map *map)
// {
// 	map->map_array = NULL;
// 	map->map_height = 0.0;
// 	map->map_width = 0.0;
// }
// 
// static void init_player(t_player *player)
// {
// 	player->direction = 0.0;
// 	player->fov = 0.0;
// 	player->x = 0.0;
// 	player->y = 0.0;
// }
// 
// static void	init_calc(t_calc *calc)
// {
// 	calc->ray_angle = 0.0;
// 	calc->ray_vect_x = 0.0;
// 	calc->ray_vect_y = 0.0;
// 	calc->wall_x = 0.0;
// 	calc->wall_y = 0.0;
// 	calc->wall_bottom = 0;
// 	calc->wall_dist = 0.0;
// 	calc->wall_height = 0.0;
// 	calc->wall_top = 0;
// }

int init(t_data *data)
{
	// Set data structure to 0
	ft_bzero(data, sizeof(t_data));
	// Init mlx
	if (!(data->mlx = mlx_init()))
		return (ft_putstr_fd("Failed to init mlx\n", 2), 0);
	// Open new window
    if (!(data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE)))
	{
		mlx_destroy_display(data->mlx);
		return (ft_putstr_fd("Failed to open window\n", 2), 0);
	}
	// Init image
	data->img = ft_calloc(sizeof(t_img), 1);
	if (data->img == NULL)
		return (ft_putstr_fd("Failed to allocate new image\n", 2), 0);

	if (!init_img(data->img, data->mlx))
		return (0);
	return (1);
}

int	init_img(t_img *img, void *mlx)
{
	if (!(img->ptr = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT)))
		return (ft_putstr_fd("Failed to init new image\n", 2), 0);
    if (!(img->data = mlx_get_data_addr(img->ptr, &(img->bpp),
		&(img->line_len), &(img->endian))))
		return (ft_putstr_fd("Failed to get new image data\n", 2), 0);
	return (1);
}
