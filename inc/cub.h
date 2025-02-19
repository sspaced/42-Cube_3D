#ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include "mlx.h"
# include <stdbool.h>
# include "libft.h"
# include <fcntl.h>
# include <math.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 7
# define KEY_A 1
# define KEY_S 0x0053
# define KEY_D 0x0044
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_PRESS_MASK 1L<<0
# define KEY_RELEASE_MASK 1L<<1
# define POINTER_MOTION_MASK 1L<<6
# define BUTTON_PRESS_MASK 1L<<2
# define BUTTON_RELEASE_MASK 1L<<3
# define LBUTTON 1
# define RBUTTON 3
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define BUTTON_PRESS 4
# define BUTTON_RELEASE 5
# define MOTION_NOTIFY 6
# define DESTROY_NOTIFY 17
# define WIN_TITLE "Cube 3D"
# define MOVE_SPEED 0.05
# define ROTATION_SPEED 1.0  
# define FOV 80
# define PI 3.14159265359
# define RAD(x) (x * PI / 180.0)
# define CEILING 0x444444
# define WALL_COLOR 0xA0CCDA
# define FLOOR 0xDAB785

# define BONUS true
# define DEBUG false

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 40684
# endif

typedef struct s_keys {
    int up;
    int down;
    int left;
    int right;
	int w;
	int a;
	int s;
	int d;
	int	m_left;
	int	m_right;
    int esc;
} t_keys;

typedef enum s_texture {
	WALL_N,
	WALL_S,
	WALL_E,
	WALL_W,
	PLAYER_DOT,
	ARM_STATIC,
	ARM_RUNNING,
	ARM_PUNCHING,
	ARM_FINGER,
} e_texture;

typedef struct s_vect {
	int x;
	int y;
} t_vect;

typedef struct s_fvect {
	double x;
	double y;
} t_fvect;

typedef struct s_calc
{
	double ray_vect_x;
	double ray_vect_y;
	int		ray_x;
	int		ray_y;
	double wall_x;
	double wall_y;
	double wall_height;
	int wall_top;
	int wall_bottom;
	double perp_wall_dist;
	int side;
	char wall_orientation;
} t_calc;

typedef	struct s_player {
	float	x;
	float	y;
	double	angle;
	float	fov;
	int	direction;
} t_player;

typedef struct s_map_info {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f[3];
	int 	c[3];
} t_map_info;

typedef	struct s_map {
	char	**map_array;
	int		map_height;
	int		map_width;
	int		current_line_count;
	t_map_info	map_info;
} t_map;

typedef struct s_img {
	void	*ptr;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
} t_img;

typedef struct s_asset {
	char		*path;
	e_texture	name;
	t_img		img;
	int			width;
	int			height;
} t_asset;

typedef struct s_arm {
	t_list		*basic;
	t_list		*running;
	t_list		*punching;
	t_list		*finger;
} t_arm;

typedef	struct s_textures {
	t_asset		*wall_n;
	t_asset		*wall_s;
	t_asset		*wall_e;
	t_asset		*wall_w;
	t_asset		*player_dot;
} t_textures;

typedef struct s_data {
    void    	*mlx;
    void    	*win;
	t_img		img;
	t_map		map;
	t_player	player;
	t_keys		keys;
	t_calc		calc;
	t_arm		arm;
	t_textures	textures;
	// textures
} t_data;

int		close_window(t_data *data);
int		key_hook(int keycode, t_data *data);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int 	mouse_click(int keycode, int x, int y, t_data *data);
int		mouse_release(int keycode, int x, int y, t_data *data);
int		mouse_move(int x, int y, t_data *data);
void	init_keys(t_keys *keys);
int handle_movement(t_data *data);

//[src/get_next_line_utils.c]
char	*get_next_line(int fd);
char	*helper(int fd, char *buffer, int bytes_read);
char	*manage_line_with_n_for_line(char *buffer, size_t index);
char	*manage_line_with_n_for_buffer(char *buffer, size_t index);
char	*read_line(int fd, char *buffer, char *previous_line, int *bytes_read);

//[src/get_next_line.c]
size_t	index_for_n(char *buffer);
int		check_eof(char *buffer, int bytes_read);

//[src/map_handler.c]
char	**read_map_file(char *file_path);
void	free_map_error(char **map);

//[src/inti.c]
void	init_data(t_data *data);
int init(t_data *data);
int	init_img(t_img *img, void *mlx);

//[src/player_utils.c]
void	set_player_pos_dir(t_data *data);

//[src/map_utils.c]
void	set_map_height_width(t_data *data);
void	map_coord_to_pixel(t_data *data, int x, int y);

//[src/display.c]
void    pixel_to_img(t_data *data, int x, int y, int color);
void	display_player_view(t_data *data);
int check_collision(t_map *map, double new_x, double new_y);
int get_player_angle(char direction);

//[src/calc.c]
void	calc_ray_vector(t_data *data, int x);
void	calc_wall_info(t_data *data);
void	calc_wall_hit(t_data *data);

//[src/cleanup.c]
void	destroy_asset(void *asset);
void	clean_mlx(t_data *data);
void	clear_animations(t_arm *arm, void *mlx);
void	destroy_animations(t_list *list, void *mlx);

//[src/assets.c]
t_list	*new_animation(void *mlx, const char *base_path, int frame_number, e_texture name);
t_asset* new_asset(void *mlx, char* path, e_texture name);
int add_asset_to_list(t_list **head, void *mlx, char *path, e_texture name);

//[src/move_player.c]
void	move_foward(t_player *player, t_map *map, double angle);
void	move_left(t_player *player, t_map *map, double angle);
void	move_backward(t_player *player, t_map *map, double angle);
void	move_right(t_player *player, t_map *map, double angle);

//[src/mouse_hooks.c]
int mouse_click(int keycode, int x, int y, t_data *data);
int mouse_release(int keycode, int x, int y, t_data *data);
int mouse_move(int x, int y, t_data *data);

//[src/parse.c]
int parser(char **argv, t_data *data, int argc);

//[src/array_utils.c]
int array_size(char **array);
void clear_array(char **array);

//[src/parse_utils.c]
int is_digit(char *str);
int is_only_space(char *line);
int is_map_part(char element);
int contain_map_part(char *line);
void err_msg(char *info, int line);

//[src/parse_info.c]
int extract_info(char *line, t_map_info *map_info);
char *search_info(char *line, char **info_type);

//[src/parse_map.c]
int extract_map(char *line, t_data *data);

//[src/parse_final_check.c]
int check_info_complete(t_map_info *map_info);
int check_player(char **map_array);
int check_close_map(char **map_array);

//[src/parse_check_directions.c]
int check_down(int x, int y, char **map_array);
int check_up(int x, int y, char **map_array);
int check_right(int x, char *map_line);
int check_left(int x, char *map_line);

//[src/parse_color.c]
int set_map_color_info(int map_info_field[3], char *info_value);

//[src/array_utils.c]
int array_size(char **array);
void clear_array(char **array);

//[src/untils.c]
char *ft_strdup_until(char *str, char until);
int ft_strlen_until(char *str, char until);

#endif
