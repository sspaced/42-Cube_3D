CC = cc
CFLAGS = -g #-Wall -Wextra -Werror
INCLUDES = -I./header -I./mlx -I./libft
MLX_PATH = mlx
MLX_FLAGS = -L$(MLX_PATH) -lmlx -L/usr/lib -lXext -lX11 -lm -lz -L./libft -lft

SRC_DIR = src
HEADER_DIR = header
BUILD_DIR = build

SRCS =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/hook.c \
		$(SRC_DIR)/get_next_line_utils.c \
		$(SRC_DIR)/get_next_line.c \
		$(SRC_DIR)/parsing.c \
		$(SRC_DIR)/map_handler.c \
		$(SRC_DIR)/init.c \
		$(SRC_DIR)/player_utils.c \
		$(SRC_DIR)/display.c \
		$(SRC_DIR)/map_utils.c \

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
HEADER = $(HEADER_DIR)/cube.h

TARGET = cube

all: $(BUILD_DIR) libft $(MLX_PATH)/libmlx.a $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(MLX_PATH)/libmlx.a:
	make -C $(MLX_PATH)

$(TARGET): $(OBJS) $(MLX_PATH)/libmlx.a
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(TARGET)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) Makefile libft
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

FORCE:

libft: FORCE
	$(MAKE) -C libft

clean:
	$(MAKE) clean -C libft
	rm -rf $(BUILD_DIR) $(OBJS)
	make -C $(MLX_PATH) clean

fclean: clean
	$(MAKE) fclean -C libft
	rm -f $(TARGET)
	make -C $(MLX_PATH) clean

re: fclean all

.PHONY: all clean fclean re