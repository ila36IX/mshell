/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:00:25 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/05 17:02:19 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ast_parser.h"

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

/**
 * ast_parse_tree - allocate the ast with invalid node included
 *
 * @lexer: the lexer
 *
 * Return: The ast or NULL if its empty.
 * NOTE: INVALID ast is an ast that contains a `INVALID_AST` node
 */
t_ast	*ast_parse_tree(t_lexer *lexer)
{
	t_ast	*ast;
	t_token	token;

	ast = NULL;
	token = lexer_peek_next_token(lexer);
	while (token.kind)
	{
		if (token.kind == TOKEN_WORD || token_is_redir_op(token))
			ast_add_simple_cmd(&ast, lexer);
		else if (token_is_connector(token))
			ast_add_connector(&ast, lexer);
		else if (token.kind == TOKEN_OPAREN)
			ast_add_subshell(&ast, lexer);
		else
			ast_add_error(&ast, token.text, token.text_len);
		if (ast_has_parse_error(ast))
			break ;
		token = lexer_peek_next_token(lexer);
	}
	return (ast);
}
