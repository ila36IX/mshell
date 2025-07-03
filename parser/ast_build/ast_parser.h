/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:46:50 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/03 17:47:10 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef AST_PARSER_H
# define AST_PARSER_H
# include "../../exec/builtins/environ.h"
# include "../lexer/lexer.h"
# define ARRAY_INIT_SIZE 2
# define SHELL_NAME "minishell"

void	skip_nested_parens(t_lexer *lexer);
t_lexer	subshell_new_lexer(t_lexer *lexer);
t_ast	*init_ast_subshell(void);
t_ast	*ast_add_subshell(t_ast **ast_head, t_lexer *lexer);

t_ast	*init_ast_simple_cmd(void);
void	ast_simple_cmd_realloc(t_ast *ast);
void	ast_simple_cmd_add_arg(t_ast *ast, t_lexer *lexer);
t_ast	*ast_add_simple_cmd(t_ast **ast_head, t_lexer *lexer);

t_ast	*ast_add_connector(t_ast **ast_head, t_lexer *lexer);

t_ast	*create_ast(t_lexer *lexer);
t_ast	*last_ast(t_ast *ast);
void	ast_add_back(t_ast **head, t_ast *new);
void	ast_redirct_realloc(t_ast *ast);
bool	ast_add_redirct(t_ast **ast_head, t_ast *ast, t_lexer *lexer);

t_ast	*ast_add_error(t_ast **ast_head, const char *tok, size_t size);
bool	ast_error_found(t_ast *ast);
bool	ast_print_error(t_ast *ast);

char	*expand_string(const char *str, size_t size);
bool	quote_removal(char *str, size_t size);

#endif
