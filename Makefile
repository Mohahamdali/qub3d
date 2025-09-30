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
		parser/find_player.c \
		recasting/set_up.c \
		recasting/building.c \
		recasting/recast_helpers.c \
		recasting/mouvment.c \
		draw_tex/load_textures.c

OBJ = $(SRCS:.c=.o)
NAME = qub3d

CC = cc
CFLAGS =

RM = rm -f
MLX_INC =
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit -Ofast

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) -o $(NAME)

%.o: %.c qub3d.h
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
