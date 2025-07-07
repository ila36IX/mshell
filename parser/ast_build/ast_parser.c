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
	ast->redir_capacity = buff_size;
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
	t_word	target;

	if (ast->redir_capacity == ast->redir_size)
		ast_redirct_realloc(ast);
	token = lexer_next_token(lexer);
	ast->redir[ast->redir_size].type = tok_kind_to_redir_type(token.kind);
	token = lexer_next_token(lexer);
	if (token.kind != TOKEN_WORD)
	{
		ast_add_error(ast_head, token.text, token.text_len);
		return (false);
	}
	target.len = token.text_len;
	target.text = token.text;
	ast->redir[ast->redir_size++].word_target = target;
	return (true);
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
