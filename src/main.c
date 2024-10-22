#include "cube.h"

// int main(void)
// {
//     t_data  data;

//     data.mlx = mlx_init();
//     if (!data.mlx)
// 		return (1);
//     data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
//     if (!data.win)
//     {
//         free(data.mlx);
//         return (1);
//     }
	
// 	mlx_key_hook(data.win, key_hook, &data);
// 	mlx_hook(data.win, DESTROY_NOTIFY, 0, close_window, &data);
//     mlx_loop(data.mlx);
//     return (0);
// }

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_putstr_fd("Invalid argument\n", 2), 0);
	else
	{
		if (!check_file_path(argv[1]))
			return (ft_putstr_fd("Invalid path\n", 2), 0);
		char **map = read_map_file(argv[1]);
		int i = 0;
		while (1)
		{
			if (map[i] == NULL)
				break ;
			printf("%s", map[i]);
			i++;
		}
	}
}
