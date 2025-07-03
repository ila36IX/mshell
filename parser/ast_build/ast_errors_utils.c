/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_errors_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:47:02 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/03 17:47:10 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_parser.h"

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

t_ast	*ast_add_error(t_ast **ast_head, const char *tok, size_t size)
{
	t_ast	*ast;

	if (!tok || !tok)
	{
		PANIC("Format and the details must not be null");
	}
	ast = ft_calloc(1, sizeof(t_ast));
	ast->type = AST_INVALID;
	printf("bash: syntax error near unexpected token `%.*s'", (int)size, tok);
	ast_add_back(ast_head, ast);
	return (ast);
}
