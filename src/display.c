#include "cube.h"

void	pixel_to_img(t_data *data, int x, int y)
{
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
		*(unsigned int *)(data->win + (x * (data->win)) + (y * f->sl)) = f->co;
}