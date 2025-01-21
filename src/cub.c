/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elleroux <elleroux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:15 by elleroux          #+#    #+#             */
/*   Updated: 2025/01/20 19:50:51 by elleroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_asset* new_asset(t_data data, char* path)
{
	t_asset	*new;

	new = ft_calloc(sizeof(t_asset), 1);
	if (!new)
		return (printf("Failed to allocate new aeest.\n"), NULL);
	new->path = path;

	new->img_ptr = mlx_xpm_file_to_image(data.mlx, new->path, &(new->width), &(new->height));

	if (new->img_ptr == NULL)
	{
		free(new);
		return(printf("Failed to open %s.\n", new->path), NULL);
	}

	new->data = mlx_get_data_addr(new->img_ptr, &(new->bpp), &(new->line_len), &(new->endian));
	return(new);
}

t_list* init_asset(t_data data, char* name, int frame_number)
{
	int i;
	t_list*	head;
	
	i = -1;
	head = NULL;
	char* base_path = ft_strjoin("assets/img/", name);
	char* path = ft_strdup(base_path);
	while (++i < frame_number)
	{
		path = ft_strjoin(path, ft_itoa(i));
		path = ft_strjoin(path, ".xpm");
		ft_lstadd_back(&head, ft_lstnew(new_asset(data, path)));
		path = ft_strdup(base_path);
	}
	ft_lstlast(head)->next = head;
	return (head);
}

int check_args(int ac, char **av)
{
	if (ac != 2)
		return (ft_putstr_fd("Program need 1 argument\n", 2), 0);
	if (!check_file_path(av[1]))
		return (ft_putstr_fd("Invalid file name (expect .cub file)\n", 2), 0);
	return (1);
}

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
	if (!init_img(&(data->img), data->mlx))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data  data;

	// Checking args
	if (!check_args(argc, argv))
		return (0);

	// Init all data
	if (!init(&data))
		return (0);

	data.map.map_array = read_map_file(argv[1]);
	set_map_height_width(&data);
	set_player_pos_dir(&data);

	mlx_hook(data.win, KEY_PRESS, KEY_PRESS_MASK, key_press, &data);    // KeyPress
    mlx_hook(data.win, KEY_RELEASE, KEY_RELEASE_MASK, key_release, &data);  // KeyRelease
	
	if (BONUS)
	{
		mlx_hook(data.win, MOTION_NOTIFY, POINTER_MOTION_MASK, mouse_move, &data);
		mlx_mouse_hide(data.mlx, data.win);
		mlx_hook(data.win, BUTTON_PRESS, BUTTON_PRESS_MASK, mouse_click, &data);
		mlx_hook(data.win, BUTTON_RELEASE, BUTTON_RELEASE_MASK, mouse_release, &data);

		data.player_dot = new_asset(data, "assets/img/player_dot/player_dot.xpm");
		data.arm_running = init_asset(data, "arm_running_fast/", 21);
		data.arm_static = init_asset(data, "arm/", 46);
		data.arm_finger = init_asset(data, "arm_finger/", 17);
	}

	data.text_n = new_asset(data, "assets/img/text_n/text_n.xpm");
	data.text_s = new_asset(data, "assets/img/text_s/text_s.xpm");
	data.text_e = new_asset(data, "assets/img/text_e/text_e.xpm");
	data.text_w = new_asset(data, "assets/img/text_w/text_w.xpm");

    mlx_hook(data.win, DESTROY_NOTIFY, 0, close_window, &data);
    mlx_loop_hook(data.mlx, handle_movement, &data);

	display_player_view(&data);
    mlx_loop(data.mlx);
	free_map_error(data.map.map_array);
	return (1);
}

