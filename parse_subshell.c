#include "parser.h"

void	skip_nested_parens(t_lexer *lexer)
{
	t_token	token;
	int		depth;

	token = lexer_next_token(lexer);
	depth = 1;
	while (token.kind)
	{
		if (token.kind == TOKEN_OPAREN)
			depth++;
		else if (token.kind == TOKEN_CPAREN)
			depth--;
		if (token.kind == TOKEN_CPAREN && depth == 0)
			break ;
		token = lexer_next_token(lexer);
	}
}

t_lexer	subshell_new_lexer(t_lexer *lexer)
{
	size_t	cursor_loc;
	t_lexer	sub_lexer;
	size_t	lexer_size;

	lexer_next_token(lexer); /* skip open parent */
	cursor_loc = lexer->cursor;
	skip_nested_parens(lexer);
	lexer_size = lexer->cursor - cursor_loc - 1;
	sub_lexer = lexer_new(&lexer->content[cursor_loc], lexer_size);
	return (sub_lexer);
}

t_ast	*init_ast_subshell(void)
{
	t_ast	*ast;

	ast = ft_calloc(1, sizeof(t_ast));
	ast->type = AST_SUBSHELL;
	ast->redir_size = 0;
	ast->redir = ft_calloc(ARRAY_INIT_SIZE, sizeof(t_redirect));
	ast->_buff_size = ARRAY_INIT_SIZE;
	return (ast);
}

bool	is_valid_subshell(t_ast **ast_head, t_lexer *lexer)
{
	char	*token_str;

	if (!lexer_check_parens(lexer))
	{
		token_str = alloc_token_str(lexer_peek_next_token(lexer));
		ast_add_error(ast_head, ERR_UNEXPECTED_TOK, token_str);
		return (false);
	}
	if (!last_ast(*ast_head))
		return (true);
	if (last_ast(*ast_head)->type != AST_CONNECTOR)
	{
		token_str = alloc_token_str(lexer_peek_next_token(lexer));
		ast_add_error(ast_head, ERR_UNEXPECTED_TOK, token_str);
		return (false);
	}
	return (true);
}

t_ast	*ast_add_subshell(t_ast **ast_head, t_lexer *lexer)
{
	t_ast	*ast;
	t_token	token;
	t_lexer	sub_lexer;

	if (!is_valid_subshell(ast_head, lexer))
		return (NULL);
	sub_lexer = subshell_new_lexer(lexer);
	ast = init_ast_subshell();
	ast->subshell = create_ast(&sub_lexer);
	if (ast->subshell == NULL)
	{
		ast_add_error(ast_head, ERR_UNEXPECTED_TOK, "empty subshell");
		return (NULL);
	}
	token = lexer_peek_next_token(lexer);
	while (token_is_redir_op(token))
	{
		if (!ast_add_redirct(ast_head, ast, lexer))
			return (ast);
		token = lexer_peek_next_token(lexer);
	}
	ast_add_back(ast_head, ast);
	return (ast);
}
