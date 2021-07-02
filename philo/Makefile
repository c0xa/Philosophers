NAME		= philo
SRCDIR		= src/
SRC			= philo.c

SOURCES		= $(addprefix $(SRCDIR),$(SRC))
OBJ			= $(SOURCES:.c=.o)
CC			= gcc
CFLAGS		= -Iinc/ -Wall -Wextra -Werror

.c.o:
			$(CC) $(CFLAGS) -g -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ)
			$(CC) -g -o $(NAME) $(OBJ)

all:		$(NAME)

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean fclean re