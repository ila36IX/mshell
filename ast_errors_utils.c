#include "parser.h"

bool	ast_error_found(t_ast *ast)
{
	bool	found;

	found = false;
	while (ast && !found)
	{
		if (ast->type == AST_SUBSHELL)
			found = ast_error_found(ast->subshell);
		if (ast->type == AST_INVALID)
			return (true);
		ast = ast->next;
	}
	return (found);
}

bool	ast_print_error(t_ast *ast)
{
	bool	found;

	found = false;
	while (ast && !found)
	{
		if (ast->type == AST_SUBSHELL)
			found = ast_print_error(ast->subshell);
		if (ast->type == AST_INVALID && !found)
		{
			printf(ast->reason[0], ast->reason[1]);
			return (true);
		}
		ast = ast->next;
	}
	return (found);
}

t_ast	*ast_add_error(t_ast **ast_head, const char *format, const char *tok)
{
	t_ast	*ast;

	if (!tok || !format)
	{
		PANIC("Format and the details must not be null");
	}
	ast = ft_calloc(1, sizeof(t_ast));
	ast->type = AST_INVALID;
	ast->reason[0] = format;
	ast->reason[1] = tok;
	ast_add_back(ast_head, ast);
	return (ast);
}
