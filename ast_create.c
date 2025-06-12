#include "parser.h"

t_ast	*last_ast(t_ast *ast)
{
	while (ast && ast->next)
		ast = ast->next;
	return (ast);
}

void	ast_add_back(t_ast **head, t_ast *new)
{
	if (!head || !new)
		return ;
	while (*head)
		head = &(*head)->next;
	*head = new;
}

void	ast_redirct_realloc(t_ast *ast)
{
	size_t		buff_size;
	t_redirect	*buff;
	size_t		i;

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

/**
 * ast_add_redirct - add redirect with its target to ast node
 *
 * @ast: node to a valid ast
 * @lexe: Next token expected to be redirect op
 *
 * Return: false if the target is invalid, true if target is valid
 * invalid ast node will be added
 */
bool	ast_add_redirct(t_ast **ast_head, t_ast *ast, t_lexer *lexer)
{
	t_token	token;
	char	*target;

	if (ast->_buff_size == ast->redir_size)
		ast_redirct_realloc(ast);
	token = lexer_next_token(lexer);
	ast->redir[ast->redir_size].type = tok_kind_to_redir_type(token.kind);
	token = lexer_peek_next_token(lexer);
	if (token_is_word(token) == false)
	{
		ast_add_error(ast_head, ERR_UNEXPECTED_TOK, alloc_token_str(token));
		return (false);
	}
	target = lexer_next_zip_word(lexer);
	ast->redir[ast->redir_size++].target = target;
	return (true);
}

/**
 * create_ast - allocate the ast
 *
 * @lexer: the lexer
 *
 * Return: The ast or NULl if its empty.
 * NOTE: INVALID ast is an ast that contains a `INVALID_AST` node
 */
t_ast	*create_ast(t_lexer *lexer)
{
	t_ast	*ast;
	t_token	token;

	ast = NULL;
	token = lexer_peek_next_token(lexer);
	while (token.kind)
	{
		if (token_is_word(token) || token_is_redir_op(token))
			ast_add_simple_cmd(&ast, lexer);
		else if (token_is_connector(token))
			ast_add_connector(&ast, lexer);
		else if (token.kind == TOKEN_OPAREN)
			ast_add_subshell(&ast, lexer);
		else
			ast_add_error(&ast, ERR_UNEXPECTED_TOK, alloc_token_str(token));
		if (ast_error_found(ast))
			break ;
		token = lexer_peek_next_token(lexer);
	}
	return (ast);
}
