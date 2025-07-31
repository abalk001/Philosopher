NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -I.

SRCS = dinner.c handle_stuff.c init.c monitoring.c parsing.c philo_tools.c set_stuff.c syn_utils.c time.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
