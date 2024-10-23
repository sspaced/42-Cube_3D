#include "cube.h"

static	void init_map(t_map *map)
{
	map->map_array = NULL;
	map->map_height = 0.0;
	map->map_width = 0.0;
}

static void init_player(t_player *player)
{
	player->direction = 0.0;
	player->fov = 0.0;
	player->x = 0.0;
	player->y = 0.0;
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	init_map(&data->map);
	init_player(&data->player);
}