/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_connector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:47:01 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/03 17:47:10 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_parser.h"

bool	connector_is_valid(t_ast **ast_head, t_lexer *lexer)
{
	t_token	token;

	token = lexer_peek_next_token(lexer);
	if (!last_ast(*ast_head))
	{
		ast_add_error(ast_head, token.text, token.text_len);
	}
	if (last_ast(*ast_head)->type == AST_CONNECTOR)
	{
		ast_add_error(ast_head, token.text, token.text_len);
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
	ast = ft_malloc(1, sizeof(t_ast));
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
