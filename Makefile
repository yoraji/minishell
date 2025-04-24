CC = cc

C_FLAGS = 	  # -I./include

NAME = minishell

OBJ = $(SRC:.c=.o)

SRC = 	./src/minishell.c \
		./src/signals.c \
		./src/build_in.c \
		./src/parsing_engine.c \
		./src/free.c \
		./src/env.c \
		./src/prints.c \
		./src/syntax_error.c \
		./utils/ft_split.c \
		./utils/ft_strjoin.c \
		./utils/ft_atoi.c \
		./utils/ft_strlen.c \
		./utils/ft_strdup.c \
		./utils/ft_memcpy.c \
		./utils/ft_isspace.c \

all : $(NAME)

$(NAME) : $(SRC)
		$(CC) $(C_FLAGS) -o $(NAME) $(SRC) -lreadline
fclean : clean
		rm -f $(NAME)
clean :
		rm -f $(OBJ)
		rm -f $(OBJ_BONUS)

re : fclean all

.PHONY : all clean fclean re