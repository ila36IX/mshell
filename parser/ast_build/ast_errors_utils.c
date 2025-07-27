/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_errors_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:47:02 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/05 16:22:18 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_parser.h"
#include <stdio.h>

bool	ast_has_parse_error(t_ast *ast)
{
	bool	found;

	found = false;
	while (ast && !found)
	{
		if (ast->type == AST_SUBSHELL)
			found = ast_has_parse_error(ast->subshell);
		if (ast->type == AST_INVALID)
			return (true);
		ast = ast->next;
	}
	return (found);
}

bool	ast_print_error(t_ast *ast)
{
	t_parse_err	err;
	bool		found;

	found = false;
	while (ast && !found)
	{
		if (ast->type == AST_SUBSHELL)
			found = ast_print_error(ast->subshell);
		if (ast->type == AST_INVALID && !found)
		{
			err = ast->invalid_logs;
			write(2, err.format, ft_strlen(err.format));
			write(2, err.tok, err.tok_len);
			write(2, "'\n", 2);
			return (true);
		}
		ast = ast->next;
	}
	return (found);
}

t_ast	*ast_add_error(t_ast **ast_head, const char *tok, size_t size)
{
	t_ast		*ast;
	t_parse_err	err;

	ast = ft_malloc(1, sizeof(t_ast));
	ast->type = AST_INVALID;
	err.format = SHELL_NAME ": syntax error near unexpected token `";
	if (size == 0)
	{
		err.tok = "\\0";
		err.tok_len = 2;
	}
	else
	{
		err.tok = tok;
		err.tok_len = size;
	}
	ast->invalid_logs = err;
	ast_add_back(ast_head, ast);
	return (ast);
}

/**
 * ast_check_errors - loops through ast nodes lloking for invalid node, if one
 * found an error will  be reported
 *
 * @ast: the ast head
 *
 * Return: true if ast is clean, false if error found, if error found it will be
 * printed into stderr
 */
bool	ast_check_errors(t_ast *ast)
{
	if (ast_has_parse_error(ast))
	{
		ast_print_error(ast);
		return (false);
	}
	return (true);
}
