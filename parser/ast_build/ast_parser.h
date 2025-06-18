#include "../lexer/lexer.h"
#include "../../exec/builtins/environ.h"

#define ARRAY_INIT_SIZE 16
#define ERR_UNEXPECTED_TOK "msh: syntax error near unexpected token `%s'\n"

/* parse_subshell.c */
void	skip_nested_parens(t_lexer *lexer);
t_lexer	subshell_new_lexer(t_lexer *lexer);
t_ast	*init_ast_subshell(void);
t_ast	*ast_add_subshell(t_ast **ast_head, t_lexer *lexer);

/* parse_simple_cmd.c */
t_ast	*init_ast_simple_cmd(void);
void	ast_simple_cmd_realloc(t_ast *ast);
void	ast_simple_cmd_add_arg(t_ast *ast, t_lexer *lexer);
t_ast	*ast_add_simple_cmd(t_ast **ast_head, t_lexer *lexer);

/* parse_connector.c */
t_ast	*ast_add_connector(t_ast **ast_head, t_lexer *lexer);

/* create_ast.c */
t_ast	*create_ast(t_lexer *lexer);
t_ast	*last_ast(t_ast *ast);
void	ast_add_back(t_ast **head, t_ast *new);
void	ast_redirct_realloc(t_ast *ast);
bool	ast_add_redirct(t_ast **ast_head, t_ast *ast, t_lexer *lexer);

t_ast	*ast_add_error(t_ast **ast_head, const char *format, const char *tok);
bool	ast_error_found(t_ast *ast);
bool	ast_print_error(t_ast *ast);
t_ast	*ast_add_error(t_ast **ast_head, const char *format, const char *tok);
