NAME = minishell

CC = gcc
# CFLAGS = -Wall -Wextra -Werror
CFLAGS = 
RM = rm -f

# Manually listed source files
SRCS = \
	src/minishell.c \
	src/signals.c \
	src/parsing_engine.c \
	src/Constrating_AST.c \
	src/free.c \
	src/env.c \
	src/prints.c \
	src/syntax_error.c \
	utils/ft_atoi.c \
	utils/ft_isspace.c \
	utils/ft_memcpy.c \
	utils/ft_split.c \
	utils/ft_strchr.c \
	utils/ft_strcmp.c \
	utils/ft_strdup.c \
	utils/ft_strjoin.c \
	utils/ft_strlen.c \
	build-in/build-in.c \
	build-in/cd.c \
	build-in/echo.c \
	build-in/env.c \
	build-in/export.c \
	build-in/pwd.c \
	build-in/unset.c \
	build-in/exit.c \
	build-in/pipe.c \


OBJS = $(SRCS:.c=.o)
INCLUDES = -Iincludes

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ -lreadline

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
