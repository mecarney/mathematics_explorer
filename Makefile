NAME = fractal

SRCS = main.c extras.c equations.c

INC = -I libft/

LIB = -L . -lmlx -L libft/ -lft

FRM = -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME) :
	@#make -C libft
	@#make -C minilibx_macos
	gcc -Wall -Werror -Wextra -o $(NAME) $(SRCS) $(LIB) $(INC) $(FRM)

clean:
	@#make -C libft/ clean
	@#make -C minilibx_macos/ clean
	rm -f *.o

fclean: clean
	@#make -C libft/ fclean
	rm -f $(NAME)

re: fclean all
