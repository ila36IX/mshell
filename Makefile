CC = cc
CFLAGS = -Wall -Wextra -Werror -ggdb3 -g3
LINKERS = -lft -lreadline

SRC_FILES= $(wildcard *.c)
SRC_OBJ= $(SRC_FILES:%.c=%.o)


LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
NAME=minishell

all: libft_rule $(NAME)

libft_rule:
	$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(SRC_OBJ) $(LIBFT)
	$(CC) $(SRC_OBJ) -L$(LIBFT_DIR) $(LINKERS) -o $(NAME)

clean: 
	$(RM) $(SRC_OBJ) $(OBJ_BONUS)
	$(MAKE) -s -C $(LIBFT_DIR) clean

fclean:
	$(RM) $(SRC_OBJ) $(OBJ_BONUS)
	$(RM) $(NAME)
	$(MAKE) -s -C $(LIBFT_DIR) fclean


re: fclean all

.PHONY: all libft_rule clean fclean re
.SECONDARY: $(SRC_OBJ)
