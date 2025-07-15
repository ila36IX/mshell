/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:32:03 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/05 17:20:19 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ast_parser.h"

/**
 * ast_expand_argv - helper for `ast_expand` function, it expands the argv of an
 * ast node
 *
 * @ast: the ast to be expanded, it only expand this node, doesn't go to the
 * others
 *
 * Return: Nothing.
 */
void	ast_expand_argv(t_ast *ast)
{
	size_t	i;
	char	*arg;
	t_word	word;

	init_argv(&ast->simple_cmd);
	i = 0;
	while (i < ast->simple_cmd.tok_argv.length)
	{
		word = ast->simple_cmd.tok_argv.buff[i];
		arg = expand_string(word.text, word.len);
		if (ft_strlen(arg) > 0)
		{
			quote_removal(arg, ft_strlen(arg));
			args_append(&ast->simple_cmd, arg);
		}
		i++;
	}
	i = ast->simple_cmd.argc;
	args_append(&ast->simple_cmd, NULL);
	ast->simple_cmd.argc = i;
}

bool word_contains_quote(t_word word)
{
	size_t i;

	i = 0;
	while (i < word.len)
	{
		if (word.text[i] == '"' || word.text[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

/**
 * ast_expand_redirections - ast the functions says
 * it performs quote removal and expanding in the redirection target, if
 * redirection is herdoc, the target is the content of the herdoc
 *
 * @ast: one node of ast
 */
void	ast_expand_redirections(t_ast *ast)
{
	size_t	i;
	char	*arg;
	char	*target;
	t_word	word;

	i = 0;
	while (i < ast->redir_size)
	{
		word = ast->redir[i].word_target;
		target = ast->redir[i].target;
		if (ast->redir[i].type == REDIR_TYPE_HEREDOC)
		{
			if (!word_contains_quote(word))
				ast->redir[i].target = expand_string(target, ft_strlen(target));;
		}
		else
		{
			arg = expand_string(word.text, word.len);
			quote_removal(arg, ft_strlen(arg));
			ast->redir[i].target = arg;
		}
		i++;
	}
}

/**
 * ast_expand - init argv and redirection of ast node, calling this function
 * will setup the node with its argv and redirections
 *
 * @ast: the ast to be expanded, it only expand this node, doesn't go to the
 * others
 *
 * Return: Nothing.
 */
void	ast_expand(t_ast *ast)
{

	if (!ast)
		return ;
	if (ast->type == AST_CONNECTOR || ast->type == AST_INVALID)
	{
		PANIC("Doesn't make sense to exapnd connector, does it?");
	}
	if (ast->type == AST_SIMPLE_COMMAND)
		ast_expand_argv(ast);
	ast_expand_redirections(ast);
}
