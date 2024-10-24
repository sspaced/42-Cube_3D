#ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <../mlx/mlx.h>
# include "../libft/libft.h"
# include <fcntl.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define DESTROY_NOTIFY 17
# define KEY_ESC 65307
# define WINDOW_TITLE "Cube 3D"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 40684
# endif

typedef	struct s_player {
	float	x;
	float	y;
	float	fov;
	char	direction;
} t_player;

typedef	struct s_map {
	char **map_array;
	float	map_height;
	float	map_width;
} t_map;

typedef struct s_data {
    void    		*mlx;
    void    		*win;
	struct s_map	map;
	struct s_player	player;
} t_data;

//[src/hook.c]
int		close_window(t_data *data);
int		key_hook(int keycode, t_data *data);

//[src/get_next_line_utils.c]
char	*get_next_line(int fd);
char	*helper(int fd, char *buffer, int bytes_read);
char	*manage_line_with_n_for_line(char *buffer, size_t index);
char	*manage_line_with_n_for_buffer(char *buffer, size_t index);
char	*read_line(int fd, char *buffer, char *previous_line, int *bytes_read);

//[src/get_next_line.c]
size_t	index_for_n(char *buffer);
int		check_eof(char *buffer, int bytes_read);

//[src/parsing.c]
int		check_file_path(char *path);

//[src/map_handler.c]
char	**read_map_file(char *file_path);
void	free_map_error(char **map);

//[src/inti.c]
void	init_data(t_data *data);

//[src/player_utils.c]
void	set_player_pos_dir(t_data *data);

//[src/map_utils.c]
void	set_map_height_width(t_data *data);

#endif