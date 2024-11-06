

CC = cc
NAME = philo
CFLAGS = -Wall -Wextra -Werror -g
SRC = 	main.c \
	utils.c \
	monitoring.c \
	argument_parser.c \
	philosopher_routine.c \
	thread_management.c \
	resource_management.c \
	

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I . -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME) $(OBJ)

re: fclean all

