NAME = so_long
CC = cc
CFLAGS = -Wall -Werror -Wextra -I/usr/include -Imlx_linux -O3
LDFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
SRC = $(wildcard src/*.c) $(wildcard libft/*.c)
OBJ_DIR = obj
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/src/%.o: src/%.c | $(OBJ_DIR)/src
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/libft/%.o: libft/%.c | $(OBJ_DIR)/libft
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/src $(OBJ_DIR)/libft

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
