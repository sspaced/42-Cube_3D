/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elleroux <elleroux@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:08:27 by elleroux          #+#    #+#             */
/*   Updated: 2025/01/30 18:27:25 by elleroux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// Fonction pour vérifier les collisions
int	check_collision(t_data *data, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_x < 0 || map_y < 0 || map_x >= data->map.map_width || map_y
		>= data->map.map_height || data->map.map_array[map_y][map_x] == '1')
		return (1);
	return (0);
}

inline unsigned int	get_pixel_img(t_img *img, int x, int y)
{
	return (*(unsigned int *)((img->data + (y * img->line_len)
			+ (x * img->bpp / 8))));
}

unsigned int	get_pixel_img(t_img *img, int x, int y);

inline void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x > 1920)
		x = x % 1920;
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		dst = img->data + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *) dst = color;
	}
}

void	put_pixel_img(t_img *img, int x, int y, int color);

void	put_img_to_img3(t_data *data, t_asset *src, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < src->width)
	{
		while (++j < src->height)
		{
			put_pixel_img((&data->img), x + i, y + j, get_pixel_img(&(src->img), i, j));
		}
		j = -1;
	}
}

void	play_animation(t_data *data, t_list **list)
{
	put_img_to_img3(data, (t_asset *)((*list)->content), 0, 0);
	*list = (*list)->next;
}

void	put_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;
	int	coef;

	coef = 30;
	x = x * coef;
	y = y * coef;
	i = x + coef;
	j = y + coef;
	while (--i >= x)
	{
		while (--j >= y)
		{
			if (i == x)
				put_pixel_img((&data->img), j, i, 0x000000);
			else
				put_pixel_img((&data->img), j, i, color);
		}
		put_pixel_img((&data->img), j, i, 0x000000);
		j = y + coef;
	}
}

void	display_map(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++x < data->map.map_width)
	{
		while (++y < data->map.map_height)
		{
			if (data->map.map_array[y][x] == '1')
				put_square(data, x, y, 0x666666);
			else
				put_square(data, x, y, 0xAAAAAA);
		}
		y = -1;
	}
	put_img_to_img3(data, data->textures.player_dot, data->player.y * 30, data->player.x * 30);
}

inline t_asset	*choose_texture(t_textures *textures, char wall_orientation)
{
	if (wall_orientation == 'N')
		return (textures->wall_n);
	if (wall_orientation == 'S')
		return (textures->wall_s);
	if (wall_orientation == 'E')
		return (textures->wall_e);
	if (wall_orientation == 'W')
		return (textures->wall_w);
	return (NULL);
}

t_asset	*choose_texture(t_textures *textures, char wall_orientation);

void	draw_textured_wall(t_textures *textures, t_calc *calc, t_img *img)
{
	int	tex_x;
	t_asset	*current_texture;
	int	text_size;
	double step;
	double tex_pos;

	current_texture = choose_texture(textures, calc->wall_orientation);
	text_size = current_texture->img.line_len / 4;
	tex_x = (int)(calc->wall_x * text_size) & text_size - 1; // Supposons que les textures font 64x64
	step = 1.0 * current_texture->height / calc->wall_height;
	tex_pos = (calc->wall_top - WIN_HEIGHT / 2 + calc->wall_height / 2) * step;
	while (calc->ray_y < calc->wall_bottom)
	{
		int tex_y = (int)tex_pos & (current_texture->height - 1);
		tex_pos += step;
		unsigned int color = get_pixel_img(&(current_texture->img), tex_x, tex_y);
		put_pixel_img(img, calc->ray_x, calc->ray_y++, color);
	}
}

void display_player_view(t_data *data)
{
	data->calc.ray_x = 0;
	data->calc.ray_y = 0;
	// draw each column of the screen one by one
    while(data->calc.ray_x < WIN_WIDTH)
    {
		// initial calc
		calc_ray_vector(data, data->calc.ray_x);
		calc_wall_hit(data);
		calc_wall_info(data);
		// drawing of celling
		while (data->calc.ray_y < data->calc.wall_top)
			put_pixel_img((&data->img), data->calc.ray_x, data->calc.ray_y++, CEILING);
		// drawing of wall
		draw_textured_wall(&(data->textures), &(data->calc), &(data->img));
		// Drawing of floor
		while (data->calc.ray_y < WIN_HEIGHT)
			put_pixel_img(&(data->img), data->calc.ray_x, data->calc.ray_y++, FLOOR);
		data->calc.ray_x++;
	}
	if (BONUS)
	{
		t_keys	empty;

		ft_bzero(&empty, sizeof(t_keys));
		if (ft_memcmp(&(data->keys), &empty, sizeof(t_keys)) == 0)
			play_animation(data, &(data->arm.basic));
		else if (data->keys.m_right == 1)
			play_animation(data, &(data->arm.finger));
		else if (data->keys.m_left == 1)
			play_animation(data, &(data->arm.punching));
		else
			play_animation(data, &(data->arm.running));
		display_map(data);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
}

int	get_player_angle(char direction)
{
	if (direction == 'N')
		return (270);
	if (direction == 'S')
		return (90);
	if (direction == 'E')
		return (0);
	if (direction == 'W')
		return (180);
	return (0);
}
