NAME = test
CC = cc
CFLAGS = #-Wall -Wextra -Werror
SRC_DIR = src/
HEADER_DIR = header/
FLAGS = -L./libft -lft

SRC = $(SRC_DIR)main_test.c \
      $(SRC_DIR)parsing.c \
      $(SRC_DIR)get_next_line.c \
      $(SRC_DIR)get_next_line_utils.c \

OBJ = $(SRC:.c=.o)

all: libft $(NAME)

libft:
	$(MAKE) -C libft

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -Ilibft -c $< -o $@

clean:
	$(MAKE) clean -C libft
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft