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

MLX_DIR = ./minilibx-linux
MLX_INC = -I$(MLX_DIR)
MLX_LIB = -L$(MLX_DIR)

MLXFLAGS = -lmlx -lXext -lX11 -lm -lGL -lbsd -Ofast

all: $(NAME)

# Link rule now depends on mlx/libmlx.a
$(NAME): $(OBJ) $(MLX_DIR)/libmlx.a
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) $(MLXFLAGS) -o $(NAME)

# Auto-build mlx before linking
$(MLX_DIR)/libmlx.a:
	$(MAKE) -C $(MLX_DIR)

%.o: %.c qub3d.h
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all
