#include "parser.h"

t_ast *last_ast(t_ast *ast)
{
	while (ast && ast->next)
		ast = ast->next;
	return (ast);
}

void ast_add_back(t_ast **head, t_ast *new)
{
	if (!head || !new)
		return;
	while (*head)
		head = &(*head)->next;
	*head = new;
}

void ast_redirct_realloc(t_ast *ast)
{
	size_t	    buff_size;
	t_redirect *buff;
	size_t	    i;

	buff_size = ast->redir_size * 2;
	buff = ft_calloc(buff_size, sizeof(t_redirect));
	i = 0;
	while (i < ast->redir_size)
	{
		buff[i] = ast->redir[i];
		i++;
	}
	ast->redir = buff;
	ast->_buff_size = buff_size;
}

void ast_add_redirct(t_ast *ast, t_lexer *lexer)
{
	t_token token;
	char   *target;

	if (ast->_buff_size == ast->redir_size)
		ast_redirct_realloc(ast);
	token = lexer_next_token(lexer);
	ast->redir[ast->redir_size].type = tok_kind_to_redir_type(token.kind);
	token = lexer_peek_next_token(lexer);
	if (token_is_word(token) == false)
	{
		printf(ERR_UNEXPECTED_TOK, alloc_token_str(token));
		TODO("hanlde redirection errors");
	}
	target = lexer_next_zip_word(lexer);
	ast->redir[ast->redir_size++].target = target;
}

t_ast *create_ast(t_lexer *lexer)
{
	t_ast *ast;

	ast = NULL;
	while (lexer_peek_next_token(lexer).kind)
	{
		ast_try_add_simple_cmd(&ast, lexer);
		ast_try_add_connector(&ast, lexer);
		ast_try_add_subshell(&ast, lexer);
	}
	return (ast);
}

