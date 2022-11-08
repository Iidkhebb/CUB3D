NAME = cub3D
CFLAGS = -Wall -Wextra -Werror
FRAME = -lmlx -framework OpenGL -framework AppKit -Oz
CC = cc

INC =  includes/cub3d.h
SRCS = main.c src/parsing/__init__.c src/parsing/parsing_utils.c src/parsing/scrape_value.c  \
src/parsing/map_list_utils.c src/draw/__mlx_init__.c src/draw/player.c src/draw/mini_map.c  \
src/draw/rays.c src/parsing/init_extra.c src/parsing/garbage.c src/parsing/scrape_extra.c \
src/parsing/check_wall.c src/draw/rays_extra.c src/draw/mlx_calc.c src/draw/keys.c \
src/parsing/check_map.c src/parsing/valid_text.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = LIBFT
LIBFT_LIB = $(LIBFT_DIR)/libft.a


GNL_DIR = GNL
GNL_LIB = $(GNL_DIR)/line.a


all: $(NAME)
	@$(CC) $(CFLAGS) $(LIBFT_LIB) $(GNL_LIB) $(OBJS) $(FRAME) -o $(NAME)
$(NAME): $(OBJS) $(INC) $(LIBFT_LIB) $(GNL_LIB)
	@echo "\x1B[34mcompiling Project...\x1B[33m"

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(GNL_LIB):
	@$(MAKE) -C $(GNL_DIR)

clean:
	@$(RM) $(OBJS)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(GNL_DIR)
	@echo "successfuly cleaned..."

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(MAKE) fclean -C $(GNL_DIR)
	@echo "removed successfuly..."

re: fclean all