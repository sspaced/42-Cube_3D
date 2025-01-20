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

int	main(int argc, char **argv)
{
	t_data  data;

	if (argc != 2)
		return (ft_putstr_fd("Invalid argument\n", 2), 0);
	if (!check_file_path(argv[1]))
		return (ft_putstr_fd("Invalid path\n", 2), 0);
	init_data(&data);
	init_keys(&data.keys);
	data.mlx = mlx_init();
    if (!data.mlx)
		return (1);
    data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    if (!data.win)
		return (free(data.mlx), 1);
	init_img(&data);
	data.map.map_array = read_map_file(argv[1]);
	set_map_height_width(&data);
	set_player_pos_dir(&data);

	// printf("height = %d width = %d\n", data.map.map_height, data.map.map_width);
	// printf("x = %f y = %f d = %c\n", data.player.x, data.player.y, data.player.direction);

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

