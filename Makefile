NAME = philo
SRC = src/philosophers.c
HEADERS = -I ./include
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
THREADFLAGS = -pthread
OBJ = $(addprefix obj/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(THREADFLAGS) $(OBJ) -o $(NAME)

obj/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(THREADFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re