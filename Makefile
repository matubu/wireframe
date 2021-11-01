NAME = fdf
OBJ = bin/fdf.o bin/math.o bin/mlx.o
BIN = bin
FLAGS = -Wall -Wextra -Werror

OS = $$(uname -s)

ECHO = echo
RED = \033[31m
GRE = \033[32m
GRA = \033[37m
BLU = \033[34m
EOC = \033[0m

all: $(NAME)

bin:
	@$(ECHO) "$(GRE)● Creating /$(BIN) 📁$(EOC)"
	@mkdir -p $(BIN)

bin/%.o: %.c
	@$(ECHO) "$(BLU)● Compiling $^ 🔧$(EOC)"
	@gcc $(FLAGS) -c -I/usr/local/include $^ -o $@

$(NAME): bin $(OBJ)
	@if [ $(OS) = 'Linux' ]; then \
		$(ECHO) "$(BLU)● Compiling to binary ⚙️  $(GRA)(Linux 🐧 mode)$(EOC)"; \
		gcc $(FLAGS) -L/usr/local/lib $(OBJ) -o $(NAME) -lm -lmlx -lXext -lX11 -lz; \
	else \
		$(ECHO) "$(BLU)● Compiling to binary ⚙️  $(GRA)(maxOS 🍎 mode)$(EOC)"; \
		gcc $(FLAGS) -l mlx -framework OpenGL -framework AppKit $(OBJ) -o $(NAME) -lm; \
	fi

clean:
	@$(ECHO) "$(RED)● Removing /$(BIN) 📁$(EOC)"
	@rm -rf $(BIN)

fclean: clean
	@$(ECHO) "$(RED)● Removing binary ⚙️ $(EOC)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
