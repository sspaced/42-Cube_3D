/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:08:27 by elleroux          #+#    #+#             */
/*   Updated: 2025/02/24 14:15:51 by lben-adi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

unsigned int	get_pixel_img(t_img *img, int x, int y)
{
	return (*(unsigned int *)((img->data + (y * img->line_len) + (x * img->bpp
				/ 8))));
}

void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x > 1920)
		x = x % 1920;
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		dst = img->data + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

void	put_img_to_img3(t_data *data, t_asset *src, int x, int y)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < src->width)
	{
		while (++j < src->height)
			put_pixel_img(&data->img, x + i, y + j, get_pixel_img(&src->img, i,
					j));
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
