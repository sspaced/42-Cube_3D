# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elleroux <elleroux@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/27 14:18:05 by elleroux          #+#    #+#              #
#    Updated: 2024/11/27 15:01:48 by elleroux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### CONFIG ###
TARGET	= cub
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
INCLUDE	= -Iinc -Ilib/libft -Ilib/mlx
LFLAGS	= -lft -lmlx -lm -lX11 -lXext
LIBFT	= lib/libft/libft.a
MLX		= lib/mlx/libmlx.a
DEBUG	= -g3


### SOURCES ###
EXTENSION	= .c
SRC_DIR		= src
BUILD_DIR	= .build
LIBFT_DIR	= lib/libft
MLX_DIR		= lib/mlx
SRCS		= cub.c \
			  hook.c \
			  get_next_line_utils.c \
			  get_next_line.c \
			  parsing.c \
			  map_handler.c \
			  init.c \
			  player_utils.c \
			  display.c \
			  map_utils.c \
			  calc.c 


### OBJECTS ###
OBJS = $(addprefix $(BUILD_DIR)/, ${SRCS:$(EXTENSION)=.o})


### RULES ###
all: $(LIBFT) $(MLX) $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(TARGET): ${OBJS}
	$(CC) $(CFLAGS) -L$(LIBFT_DIR) -L$(MLX_DIR) -o $@ ${OBJS} $(LFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%$(EXTENSION) Makefile $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	make clean -C lib/libft
	make clean -C lib/mlx
	rm -rf $(BUILD_DIR)

fclean: clean
	make fclean -C lib/libft
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
