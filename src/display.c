#include "cub.h"

// Fonction pour vérifier les collisions
int check_collision(t_data *data, double new_x, double new_y)
{
    int map_x = (int)new_x;
    int map_y = (int)new_y;
    
    if (map_x < 0 || map_y < 0 || 
        map_x >= data->map.map_width || 
        map_y >= data->map.map_height ||
        data->map.map_array[map_y][map_x] == '1')
        return 1;
    return 0;
}

inline unsigned int	get_pixel_img(t_img *img, int x, int y)
{
	return (*(unsigned int *)((img->data + (y * img->line_len) + (x * img->bpp / 8))));
}

unsigned int	get_pixel_img(t_img *img, int x, int y);

inline void	put_pixel_img(t_data *img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0xFF000000)
		return ;
	if (x > 1920)
		x = x % 1920;
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT) {
		dst = img->img.data + (y * img->img.line_len + x * (img->img.bpp / 8));
		*(unsigned int *) dst = color;
	}
}

void	put_pixel_img(t_data *img, int x, int y, int color);

void	put_img_to_img3(t_data *dst, t_asset *src, int x, int y)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while(++i < src->width)
	{
		while (++j < src->height)
		{
			put_pixel_img(dst, x + i, y + j, get_pixel_img(&(src->img), i, j));
		}
		j = -1;
	}
}

void play_animation(t_data *data, t_list **list)
{

	put_img_to_img3(data, (t_asset*)((*list)->content), 0, 0);
	*list = (*list)->next;
}

void put_square(t_data *data, int x, int y, int color)
{
	int	 i;
	int	 j;
	int coef;

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
				put_pixel_img(data, j, i, 0x000000);
			else
				put_pixel_img(data, j, i, color);
		}
		put_pixel_img(data, j, i, 0x000000);
		j = y + coef;
	}
}

void display_map(t_data *data)
{
	int	 x;
	int	 y;

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
	put_img_to_img3(data, data->player_dot, data->player.y * 30, data->player.x * 30);
}

void display_player_view(t_data *data)
{
    int x;
	int y;

	x = 0;
    while(x < WIN_WIDTH)
    {
		calc_ray_vector(data, x);
		calc_wall_hit(data);
		calc_wall_info(data);
		y = 0;
		while (y < data->calc.wall_top)
			put_pixel_img(data, x, y++, CEILING);

		// Dessiner le mur texturé
        int tex_x = (int)(data->calc.wall_x * 64.0) & 63; // Supposons que les textures font 64x64
        
        t_asset *current_texture;
        switch(data->calc.wall_orientation)
        {
            case 'N': current_texture = data->text_n; break;
            case 'S': current_texture = data->text_s; break;
            case 'E': current_texture = data->text_e; break;
            case 'W': current_texture = data->text_w; break;
        }
        
        double step = 1.0 * current_texture->height / data->calc.wall_height;
        double tex_pos = (data->calc.wall_top - WIN_HEIGHT / 2 + data->calc.wall_height / 2) * step;
        
        while (y < data->calc.wall_bottom)
        {
            int tex_y = (int)tex_pos & (current_texture->height - 1);
            tex_pos += step;
            unsigned int color = get_pixel_img(&(current_texture->img), tex_x, tex_y);
			put_pixel_img(data, x, y++, color);
        }

		while (y < WIN_HEIGHT)
			put_pixel_img(data, x, y++, FLOOR);
		x++;
    }

	if (BONUS)
	{
		t_keys empty;
		ft_bzero(&empty, sizeof(t_keys));
		if (ft_memcmp(&(data->keys), &empty, sizeof(t_keys)) == 0)
			play_animation(data, &(data->arm_static));
		else if (data->keys.m_right == 1)
			play_animation(data, &(data->arm_finger));
		else if (data->keys.m_left == 1)
			play_animation(data, &(data->arm_punching));
		else
			play_animation(data, &(data->arm_running));
		display_map(data);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
	// mlx_put_image_to_window(data->mlx, data->win, data->asset->img_ptr, 0, 0);
}

int get_player_angle(char direction)
{
    switch (direction)
    {
        case 'N': return 270;
        case 'S': return 90;
        case 'E': return 0;
        case 'W': return 180;
        default: return 0;
    }
}
