CC = cc
CFLAGS = -Wall -Wextra -Werror -ggdb3 -g3
LINKERS = -lft -lreadline

SRC_FILES= $(wildcard ../*.c)
SRC_OBJ= $(SRC_FILES:%.c=%.o)


LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

lexer="test_lexer"
LEXER_FILES= $(wildcard ./test_lexer.c)
LEXER_OBJ= $(LEXER_FILES:%.c=%.o)

all: lexer
	@printf "No main function in your code!\n"

lexer: libft_rule $(SRC_OBJ) $(LEXER_OBJ)
	$(CC) $(SRC_OBJ) $(LEXER_OBJ) -L$(LIBFT_DIR) $(LINKERS) -o $(lexer)

libft_rule:
	$(MAKE) -s -C $(LIBFT_DIR)

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
