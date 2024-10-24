#include "cube.h"

int	main(int argc, char **argv)
{
	t_data  data;
	if (argc != 2)
		return (ft_putstr_fd("Invalid argument\n", 2), 0);
	if (!check_file_path(argv[1]))
		return (ft_putstr_fd("Invalid path\n", 2), 0);
	init_data(&data);
	data.mlx = mlx_init();
    if (!data.mlx)
		return (1);
    data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    if (!data.win)
		return (free(data.mlx), 1);
	data.map.map_array = read_map_file(argv[1]);
	set_map_height_width(&data);
	set_player_pos_dir(&data);
	printf("height = %f width = %f\n", data.map.map_height, data.map.map_width);
	printf("x = %f y = %f d = %c\n", data.player.x, data.player.y, data.player.direction);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, DESTROY_NOTIFY, 0, close_window, &data);
    mlx_loop(data.mlx);
	free_map_error(data.map.map_array);
	return (1);
}
