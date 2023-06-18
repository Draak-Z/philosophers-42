NAME		=	philo

CC			=	gcc

CFLAGS		=	-Werror -Wall -Wextra -pthread

SRCS		=	main.c threading.c utils.c

OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean		:
				rm -rf $(OBJS)

fclean		:	clean
				rm -rf $(NAME)

re			:	fclean all