NAME = fdf
SRC = fdf.c

all: $(NAME)

$(NAME): $(SRC)
	gcc -Wall -Wextra -Werror -lm -l mlx -framework OpenGL -framework AppKit $(SRC) -o $(NAME)
