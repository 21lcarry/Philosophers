SRCS		= main.c init.c utils.c utils2.c

HEADERS		= philosophers.h

OBJS		= ${SRCS:.c=.o}

CC			= gcc

RM			= rm -f

NAME		= philo

CFLAGS		= -c -Wall -Werror -Wextra

$(NAME):	${OBJS} ${HEADERS}
			$(CC) $(OBJS) $(LIBFT) $(HEADERS)  -o $(NAME) -lpthread

all:		${NAME}

clean:
			${RM} ${OBJS}
			${RM} *.o

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re