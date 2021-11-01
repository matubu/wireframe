NAME = fdf
SRC = fdf.c
FLAGS = -Wall -Wextra -Werror

OS = $$(uname -s)

all: $(NAME)

$(NAME): $(SRC)
	if [ $(OS) = 'Linux' ]; then \
		gcc $(FLAGS) -I/usr/local/include -L/usr/local/lib $(SRC) -o $(NAME) -lm -lmlx -lXext -lX11 -lz; \
	else \
		gcc $(FLAGS) -l mlx -framework OpenGL -framework AppKit $(SRC) -o $(NAME) -lm; \
	fi

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
