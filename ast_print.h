#ifndef AST_PRINT_H
# define AST_PRINT_H

# include "main.h"

# define INDENT_SIZE 8

void		print_ast(t_ast *ast);
void		print_ast_connector(t_ast *ast, int indent);
void		print_ast_redirection(t_ast *ast, int indent);
void		print_ast_simple_cmd(t_ast *ast, int indent);
void		print_ast_subshell(t_ast *ast, int indent);
void		print_ast_type(t_ast *ast, int indent);

/* Internals */
void		_print_tree_end_root(int indent);
void		_print_ast_helper(t_ast *ast, int indent);
void		_tree_line_prefix(int indent, bool is_empty_line);

/* type printings */
const char	*ast_type_to_str(t_ast_type type);
const char	*connector_type_to_str(t_connector type);
const char	*redir_type_to_str(t_redirect_type type);

#endif
