SRCS		=		main.c eat.c argument.c sleepandthink.c utils.c

OBJS		=		$(SRCS:.c=.o)

NAME		=		philo

CC			=		gcc

CFLAGS		=		-Wall -Wextra -Werror -fsanitize=thread -g

RM			=		rm -rf

all:				$(NAME)

$(NAME):			$(OBJS)
						$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
					$(RM) $(OBJS)

fclean:				clean
						$(RM) $(NAME)

re:					fclean $(NAME)

.PHONY:				all clean fclean re