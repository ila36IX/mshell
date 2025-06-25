#include "ast_parser.h"

t_ast	*ast_add_error(t_ast **ast_head, const char *format, const char *tok);

bool	connector_is_valid(t_ast **ast_head, t_lexer *lexer)
{
	char	*connector;

	if (!last_ast(*ast_head))
	{
		connector = alloc_token_str(lexer_peek_next_token(lexer));
		ast_add_error(ast_head, ERR_UNEXPECTED_TOK, connector);
	}
	if (last_ast(*ast_head)->type == AST_CONNECTOR)
	{
		connector = alloc_token_str(lexer_peek_next_token(lexer));
		ast_add_error(ast_head, ERR_UNEXPECTED_TOK, connector);
		return (false);
	}
	return (true);
}

t_ast	*ast_add_connector(t_ast **ast_head, t_lexer *lexer)
{
	t_ast	*ast;
	t_token	token;

	if (!connector_is_valid(ast_head, lexer))
		return (NULL);
	token = lexer_next_token(lexer);
	ast = ft_calloc(1, sizeof(t_ast));
	ast->next = NULL;
	ast->type = AST_CONNECTOR;
	if (token.kind == TOKEN_OR)
		ast->connector = CONNECTOR_OR;
	else if (token.kind == TOKEN_AND)
		ast->connector = CONNECTOR_AND;
	else if (token.kind == TOKEN_PIPE)
		ast->connector = CONNECTOR_PIPE;
	ast_add_back(ast_head, ast);
	return (ast);
}
