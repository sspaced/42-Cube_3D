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
