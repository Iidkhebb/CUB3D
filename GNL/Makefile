NAME = line.a
CFLAGS = -c -Wall -Werror -Wextra
CC = gcc

INC =  get_next_line.h
CFILES = get_next_line.c get_next_line_utils.c
OFILES = $(CFILES:.c=.o)


all: $(NAME)

$(NAME): $(OFILES) $(INC)
	@$(CC) $(CFLAGS) $(CFILES)
	@ar -rc $(NAME) $(OFILES)
	@echo "\x1B[34mcompiling Project...\x1B[33m"

clean:
	@$(RM) $(OFILES)
	@echo "successfuly cleaned..."

fclean: clean
	@rm -rf $(NAME)
	@echo "removed successfuly..."

re: fclean all