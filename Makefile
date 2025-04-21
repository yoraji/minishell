CC = cc

C_FLAGS = 

NAME = minishell

OBJ = $(SRC:.c=.o)

SRC = 	./src/minishell.c \
		./utils/ft_split.c \
		./utils/ft_strjoin.c \
		./utils/ft_atoi.c \
		./utils/ft_strlen.c \
		./utils/ft_strdup.c \
		./utils/ft_memcpy.c \

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