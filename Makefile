NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
HDRS = philo.h
SRCS = init_args.c main.c monitoring.c activities.c threads.c valid_args.c
OBJS = $(SRCS:.c=.o)
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -I/usr/include -O3 -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
