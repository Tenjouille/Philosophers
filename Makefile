NAME = philo
SRCS = src/philosophers.c \
		src/philosophers_utils.c \
		src/check.c \
		src/actions.c \
		src/init.c
HEADERS = -I ./include
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
THREADFLAGS = -pthread
OBJ = $(addprefix obj/, $(notdir $(SRCS:.c=.o)))

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

fullgit:
	git add $(SRCS) $(HEADERS) Makefile

re: fclean all

.PHONY: all clean fclean re