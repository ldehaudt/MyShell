NAME = minishell

FLAGS = -Wall -Wextra -Werror

SRC = minishell.c env.c support.c split.c builtins.c env_support.c

HEADER = minishell.h

LIBRARY = -L ./libft -lft

all : $(NAME)

$(NAME) : $(SRC) $(HEADER)
	make -C libft
	gcc -O3 $(FLAGS) $(LIBRARY) -I $(HEADER) $(SRC) -o $(NAME)

clean :
	rm -f *.o

fclean : clean
	make fclean -C libft
	rm -f $(NAME)

re : fclean all