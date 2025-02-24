/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:08:27 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/24 14:17:55 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_asset	*choose_texture(t_textures *textures, char wall_orientation)
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

void	draw_textured_wall(t_textures *textures, t_calc *calc, t_img *img)
{
	t_tex_calc	tex;

	tex.current_texture = choose_texture(textures, calc->wall_orientation);
	tex.text_size = tex.current_texture->img.line_len / 4;
	tex.tex_x = (int)(calc->wall_x * tex.text_size) & (tex.text_size - 1);
	tex.step = 1.0 * tex.current_texture->height / calc->wall_height;
	tex.tex_pos = (calc->wall_top - WIN_HEIGHT / 2 + calc->wall_height / 2)
		* tex.step;
	while (calc->ray_y < calc->wall_bottom)
	{
		tex.tex_y = (int)tex.tex_pos & (tex.current_texture->height - 1);
		tex.tex_pos += tex.step;
		tex.color = get_pixel_img(&(tex.current_texture->img), tex.tex_x,
				tex.tex_y);
		put_pixel_img(img, calc->ray_x, calc->ray_y++, tex.color);
	}
}

void	display_player_view(t_data *data)
{
	data->calc.ray_x = 0;
	while (data->calc.ray_x < WIN_WIDTH)
	{
		data->calc.ray_y = 0;
		calc_ray_vector(data, data->calc.ray_x);
		calc_wall_hit(data);
		calc_wall_info(data);
		while (data->calc.ray_y < data->calc.wall_top)
			put_pixel_img((&data->img), data->calc.ray_x, data->calc.ray_y++,
				CEILING);
		draw_textured_wall(&(data->textures), &(data->calc), &(data->img));
		while (data->calc.ray_y < WIN_HEIGHT)
			put_pixel_img(&(data->img), data->calc.ray_x, data->calc.ray_y++,
				FLOOR);
		data->calc.ray_x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
}
