C = cc
CFLAGS = -Wall -Wextra -Werror -ggdb3 -g3 -fsanitize=address
LINKERS = -lft -lreadline -fsanitize=address

SRC_FILES= \
./dynamic_array/array_argv.c     ./exec/builtins/unset.c       ./exec/statics.c 								./parser/ast_build/ast_parser.c 				./parser/ast_print/ast_print.c\
./dynamic_array/array_words.c    ./exec/exec_builtin.c         ./exec/status.c                                  ./parser/ast_build/ast_parse_redirec.c          ./parser/ast_print/ast_print_utils.c\
./dynamic_array/string.c         ./exec/exec.c                 ./exec/utils.c                                   ./parser/ast_build/parse_connector.c            ./parser/ast_print/ast_print_utils_extra.c\
./exec/builtins/cd.c             ./exec/exec_connector.c       ./main.c                                         ./parser/ast_build/parse_simple_cmd.c           ./parser/ast_print/ast_type_to_str.c\
./exec/builtins/echo.c           ./exec/exec_executable.c      ./parser/ast_build/ast_create.c                  ./parser/ast_build/parse_subshell.c             ./parser/lexer/lexer.c\
./exec/builtins/env.c            ./exec/exec_simple_command.c  ./parser/ast_build/ast_errors_utils.c            ./parser/ast_build/read_curr_dir_files.c        ./parser/lexer/lexer_extra.c\
./exec/builtins/environ.c        ./exec/getters.c              ./parser/ast_build/ast_expand.c                  ./parser/ast_build/wildcard_sort_files_utils.c  ./parser/lexer/lexer_parent_checker.c\
./exec/builtins/environ_extra.c  ./exec/pipe.c                 ./parser/ast_build/ast_expand_utils.c            ./parser/ast_build/wildcmp.c                    ./parser/lexer/lexer_print.c\
./exec/builtins/exit.c           ./exec/processes.c            ./parser/ast_build/ast_expnad_redir.c            ./parser/ast_build/word_expand.c                ./parser/lexer/lexer_tokens_utils.c\
./exec/builtins/export.c         ./exec/redirections.c         ./parser/ast_build/ast_fields_splitting.c        ./parser/ast_build/word_expand_extra.c          ./parser/lexer/lexer_utils.c\
./exec/builtins/pwd.c            ./exec/setters.c              ./parser/ast_build/ast_fields_splitting_utils.c  ./parser/ast_build/word_expand_utils.c          ./signals/signal_handler.c

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
