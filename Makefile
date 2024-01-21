NAME = philo

SOURCES = main.c parse_input.c init_data.c exit_handler.c time.c \
		  mutex.c print_status.c dinner.c action.c monitoring.c

OBJECTS = $(SOURCES:.c=.o)

CC = cc 
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
