/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elleroux <elleroux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:16:15 by elleroux          #+#    #+#             */
/*   Updated: 2024/11/28 14:16:18 by elleroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_asset* new_asset(t_data data, char* path)
{
	t_asset	*new;

	new = ft_calloc(sizeof(t_asset), 1);
	new->path = path;

	new->img_ptr = mlx_xpm_file_to_image(data.mlx, new->path, &(new->width), &(new->height));

	if (new->img_ptr == NULL)
		printf("Failed to open %s.\n", new->path);

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

		t_asset player_dot;
		ft_bzero(&player_dot, sizeof(t_asset));
		player_dot.path = "assets/img/player_dot/player_dot.xpm";
		player_dot.img_ptr = mlx_xpm_file_to_image(data.mlx, player_dot.path, &(player_dot.width), &(player_dot.height));
		if (player_dot.img_ptr == NULL)
			printf("Failed to open %s.\n", player_dot.path);
		player_dot.data = mlx_get_data_addr(player_dot.img_ptr, &(player_dot.bpp), &(player_dot.line_len), &(player_dot.endian));
		data.player_dot = &player_dot;

		t_asset text_n;
		ft_bzero(&text_n, sizeof(t_asset));
		text_n.path = "assets/img/text_n/text_n.xpm";
		text_n.img_ptr = mlx_xpm_file_to_image(data.mlx, text_n.path, &(text_n.width), &(text_n.height));
		if (text_n.img_ptr == NULL)
			printf("Failed to open %s.\n", text_n.path);
		text_n.data = mlx_get_data_addr(text_n.img_ptr, &(text_n.bpp), &(text_n.line_len), &(text_n.endian));
		data.text_n = &text_n;

		t_asset text_s;
		ft_bzero(&text_s, sizeof(t_asset));
		text_s.path = "assets/img/text_s/text_s.xpm";
		text_s.img_ptr = mlx_xpm_file_to_image(data.mlx, text_s.path, &(text_s.width), &(text_s.height));
		if (text_s.img_ptr == NULL)
			printf("Failed to open %s.\n", text_s.path);
		text_s.data = mlx_get_data_addr(text_s.img_ptr, &(text_s.bpp), &(text_s.line_len), &(text_s.endian));
		data.text_s = &text_s;

		t_asset text_e;
		ft_bzero(&text_e, sizeof(t_asset));
		text_e.path = "assets/img/text_e/text_e.xpm";
		text_e.img_ptr = mlx_xpm_file_to_image(data.mlx, text_e.path, &(text_e.width), &(text_e.height));
		if (text_e.img_ptr == NULL)
			printf("Failed to open %s.\n", text_e.path);
		text_e.data = mlx_get_data_addr(text_e.img_ptr, &(text_e.bpp), &(text_e.line_len), &(text_e.endian));
		data.text_e = &text_e;

		t_asset text_w;
		ft_bzero(&text_w, sizeof(t_asset));
		text_w.path = "assets/img/text_w/text_w.xpm";
		text_w.img_ptr = mlx_xpm_file_to_image(data.mlx, text_w.path, &(text_w.width), &(text_w.height));
		if (text_w.img_ptr == NULL)
			printf("Failed to open %s.\n", text_w.path);
		text_w.data = mlx_get_data_addr(text_w.img_ptr, &(text_w.bpp), &(text_w.line_len), &(text_w.endian));
		data.text_w = &text_w;

		t_list* arm_running;
		arm_running = init_asset(data, "arm_running_fast/", 21);
		data.arm_running = arm_running;

		t_list* arm_static;
		arm_static = init_asset(data, "arm/", 46);
		data.arm_static = arm_static;

		t_list* arm_finger;
		arm_finger = init_asset(data, "arm_finger/", 17);
		data.arm_finger = arm_finger;
	}
    mlx_hook(data.win, DESTROY_NOTIFY, 0, close_window, &data);
    mlx_loop_hook(data.mlx, handle_movement, &data);

	display_player_view(&data);
    mlx_loop(data.mlx);
	free_map_error(data.map.map_array);
	return (1);
}

