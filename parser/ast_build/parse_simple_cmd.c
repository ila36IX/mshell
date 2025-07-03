/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:47:05 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/03 17:47:10 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_parser.h"

/**
 * ast_simple_cmd_add_arg
	- Get next argument from the lexer and add it to the ast
 *
 * @ast: ast node of type AST_SIMPLE_COMMAND
 * @lexer: lexer
 *
 * Return: Nothing, new argumenet will be added to the argv of the ast
 **/
void	ast_simple_cmd_add_word(t_ast *ast, t_lexer *lexer)
{
	t_token	token;
	t_word	word;

	if (ast->type != AST_SIMPLE_COMMAND)
	{
		UNREACHABLE("Wrong ast type!");
		return ;
	}
	token = lexer_next_token(lexer);
	word.len = token.text_len;
	word.text = token.text;
	words_append(&ast->simple_cmd.tok_argv, word);
}

t_ast	*init_ast_simple_cmd(void)
{
	t_ast	*ast;

	ast = ft_calloc(1, sizeof(t_ast));
	ast->type = AST_SIMPLE_COMMAND;
	ft_bzero(&ast->simple_cmd, sizeof(t_simple_cmd));
	ast->simple_cmd.argv = NULL;
	ast->simple_cmd.tok_argv = words_init();
	ast->simple_cmd.capacity = ARRAY_INIT_SIZE;
	ast->redir_size = 0;
	ast->redir = ft_calloc(ARRAY_INIT_SIZE, sizeof(t_redirect));
	ast->redir_capacity = ARRAY_INIT_SIZE;
	return (ast);
}

bool	is_valid_simple_cmd(t_ast **ast_head, t_lexer *lexer)
{
	t_token	token;

	if (!last_ast(*ast_head))
		return (true);
	if (last_ast(*ast_head)->type != AST_CONNECTOR)
	{
		token = lexer_peek_next_token(lexer);
		ast_add_error(ast_head, token.text, token.text_len);
		return (false);
	}
	return (true);
}

t_ast	*ast_add_simple_cmd(t_ast **ast_head, t_lexer *lexer)
{
	t_ast	*ast;
	t_token	token;

	token = lexer_peek_next_token(lexer);
	if (!is_valid_simple_cmd(ast_head, lexer))
		return (NULL);
	ast = init_ast_simple_cmd();
	ast_add_back(ast_head, ast);
	while (token.kind)
	{
		if (token.kind == TOKEN_WORD)
			ast_simple_cmd_add_word(ast, lexer);
		else if (token_is_redir_op(token))
		{
			if (!ast_add_redirct(ast_head, ast, lexer))
				return (ast);
		}
		else
			break ;
		token = lexer_peek_next_token(lexer);
	}
	return (ast);
}
