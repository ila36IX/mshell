/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:46:50 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/05 16:49:08 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef AST_PARSER_H
# define AST_PARSER_H
# include "../../dynamic_array/arrays.h"
# include "../../exec/builtins/environ.h"
# include "../../exec/exec.h"
# include "../../exec/status.h"
# include "../../includes.h"
# include "../../signals/signal_handler.h"
# include "../lexer/lexer.h"

# define ARRAY_INIT_SIZE 4
# define SORTED_CHARS " !\"#%&'()*+,:;<=>?@[\\]^_`{|}~$"
# define MAX_FILES_IN_DIR 4242
# define PARSE_ERROR_STATUS_CODE 2
# define SIGINT_ERR_STATUS_CODE 130
# define SINGLE_QUOTE_SERIALIZER 2
# define DOUBLE_QUOTE_SERIALIZER 3

void	skip_nested_parens(t_lexer *lexer);
t_lexer	subshell_new_lexer(t_lexer *lexer);
t_ast	*init_ast_subshell(void);
t_ast	*ast_add_subshell(t_ast **ast_head, t_lexer *lexer);

t_ast	*init_ast_simple_cmd(void);
void	ast_simple_cmd_realloc(t_ast *ast);
void	ast_simple_cmd_add_arg(t_ast *ast, t_lexer *lexer);
t_ast	*ast_add_simple_cmd(t_ast **ast_head, t_lexer *lexer);

t_ast	*ast_add_connector(t_ast **ast_head, t_lexer *lexer);

t_ast	*ast_parse_tree(t_lexer *lexer);
t_ast	*last_ast(t_ast *ast);
void	ast_add_back(t_ast **head, t_ast *new);
void	ast_redirct_realloc(t_ast *ast);
bool	ast_add_redirct(t_ast **ast_head, t_ast *ast, t_lexer *lexer);

t_ast	*ast_add_error(t_ast **ast_head, const char *tok, size_t size);
bool	ast_has_parse_error(t_ast *ast);
bool	ast_print_error(t_ast *ast);

char	*expand_string(const char *str, size_t size);
bool	quote_removal(char *str, size_t size);
bool	ast_check_errors(t_ast *ast);

bool	wildcmp(char *str, char *pattern);
char	**field_splitting(char *word);
bool	expand_asterisk_into_argv(char *pattern, t_simple_cmd *argv);
void	skip_quotes(char *word, size_t *i);
bool	needs_field_splitting(char *word);
void	sort_filenames(char **arr, int n);
bool	word_is_file_pattern(char *word);
bool	ast_expand_redirections(t_ast *ast);
char	*expand_asterisk_for_redir(char *pattern);
bool	serialize_and_append(t_string *str, const char *value);
void	string_append_nbr(t_string *s, int nb);

#endif
