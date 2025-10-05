# === Source files ===
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

# === Object files ===
OBJ = $(SRCS:.c=.o)

# === Executable name ===
NAME = qub3d

# === Compiler and flags ===
CC = cc
CFLAGS = 

# === Clean command ===
RM = rm -f

# === MiniLibX paths for Linux ===
MLX_DIR = minilibx-linux
MLX_INC = -I$(MLX_DIR)
MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# === Build target ===
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_LIB) -o $(NAME)

%.o: %.c qub3d.h
	$(CC) $(CFLAGS) $(MLX_INC) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
