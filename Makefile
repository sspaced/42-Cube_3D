# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lben-adi <lben-adi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 14:18:05 by elleroux          #+#    #+#              #
#    Updated: 2025/02/24 14:14:16 by lben-adi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### CONFIG ###
TARGET			= cub3D
TARGET_BONUS	= cub3D_bonus
CC				= cc
CFLAGS			= -Werror -Wall -Wextra -g3
INCLUDE			= -Iinc -Ilib/libft -Ilib/mlx
LFLAGS			= -lft -lmlx -lm -lX11 -lXext
LIBFT			= lib/libft/libft.a
MLX				= lib/mlx/libmlx.a

### SOURCES ###
EXTENSION	= .c
SRC_DIR		= src
SRC_BONUS	= src_bonus
BUILD_DIR	= .build
BUILD_BONUS	= .build_bonus
LIBFT_DIR	= lib/libft
MLX_DIR		= lib/mlx
SRCS		= cub.c \
			  hook.c \
			  get_next_line_utils.c \
			  get_next_line.c \
			  map_handler.c \
			  init.c \
			  player_utils.c \
			  display.c \
			  map_utils.c \
			  calc.c \
			  assets.c \
			  cleanup.c \
			  move_player.c \
			  mouse_hooks.c \
			  parse.c \
			  parse_info.c \
			  parse_map.c \
			  parse_final_check.c \
			  parse_check_directions.c \
			  parse_colors.c \
			  array_utils.c \
			  parse_utils.c \
			  until.c \
			  calc_2.c \
			  display_utils.c

### OBJECTS ###
OBJS := $(addprefix $(BUILD_DIR)/, ${SRCS:$(EXTENSION)=.o})
DEPS := $(addprefix $(BUILD_DIR)/, ${SRCS:$(EXTENSION)=.d})

OBJS_BONUS := $(addprefix $(BUILD_BONUS)/, ${SRCS:$(EXTENSION)=_bonus.o})
DEPS_BONUS := $(addprefix $(BUILD_BONUS)/, ${SRCS:$(EXTENSION)=_bonus.d})

### RULES ###
all: $(LIBFT) $(MLX) $(BUILD_DIR) $(TARGET)

bonus: $(LIBFT) $(MLX) $(BUILD_BONUS) $(TARGET_BONUS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_BONUS):
	mkdir -p $(BUILD_BONUS)

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(TARGET): ${OBJS}
	$(CC) $(CFLAGS) -L$(LIBFT_DIR) -L$(MLX_DIR) -o $@ ${OBJS} $(LFLAGS)

$(TARGET_BONUS): ${OBJS_BONUS}
	$(CC) $(CFLAGS) -L$(LIBFT_DIR) -L$(MLX_DIR) -o $@ ${OBJS_BONUS} $(LFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%$(EXTENSION) Makefile $(LIBFT) $(MLX) inc/cub.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BUILD_BONUS)/%_bonus.o: $(SRC_BONUS)/%_bonus$(EXTENSION) Makefile $(LIBFT) $(MLX) inc/cub.h
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	make clean -C lib/libft
	make clean -C lib/mlx
	rm -rf $(BUILD_DIR)
	rm -rf $(BUILD_BONUS)

fclean: clean
	make fclean -C lib/libft
	rm -f $(TARGET)
	rm -f $(TARGET_BONUS)

re: fclean all

-include $(DEPS)
-include $(DEPS_BONUS)
.PHONY: all bonus clean fclean re
