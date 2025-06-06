#include "parser.h"

t_ast *ast_try_add_connector(t_ast **ast_head, t_lexer *lexer)
{
	t_ast  *ast;
	t_token token;

	token = lexer_peek_next_token(lexer);
	if (token.kind != TOKEN_PIPE && token.kind != TOKEN_OR &&
	    token.kind != TOKEN_AND)
		return (NULL);
	if (!last_ast(*ast_head))
	{
		printf(ERR_UNEXPECTED_TOK, alloc_token_str(token));
		UNIMPLEMENTED("Handle errors");
	}
	if (last_ast(*ast_head)->type != AST_SIMPLE_COMMAND && last_ast(*ast_head)->type != AST_SUBSHELL)
	{
		printf(ERR_UNEXPECTED_TOK, alloc_token_str(token));
		UNIMPLEMENTED("Handle errors");
	}
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
