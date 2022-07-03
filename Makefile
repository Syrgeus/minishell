SRC =	./src/main.c
OBJS =	$(SRC:%.c=%.o)
HEADER = ./include/minishell.h

NAME = minishell

CC	= gcc
CFLAGS = -Wall -Werror -Wextra
LFLAGS = -I /Users/$(USER)/.brew/opt/readline/include -lreadline

RM	= rm -f





all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(SRC) -o $(NAME)

.PHONY		:	all clean fclean re

clean	:
				$(RM) $(OBJS)

fclean	:		clean
				$(RM) $(NAME)

re:				fclean all