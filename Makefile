SRCS =	main.c \
		parser/lib_utils.c \
		parser/lib_utils_2.c \
		parser/lib_utils_3.c \
		parser/get_next_line.c \
		parser/upload_map.c \
		parser/check_wall.c \
		parser/upload_map_utils.c \
		parser/garbage_collector.c \
		parser/parser.c \
		parser/find_player.c

OBJ = $(SRCS:.c=.o)
NAME = qub3d
CFLAGS = -Wall -Wextra -Werror
CC = cc
RM = rm -f

all: $(NAME)



$(NAME): $(OBJ)
	$(CC) $(CFLAGS)  $(OBJ) -o $(NAME)


%.o:%.c qub3d.h
	$(CC) $(CFLAGS)  -c $< -o $@

clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all
