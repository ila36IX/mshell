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

void	read_word_into_argv(char *word, t_simple_cmd *argv)
{
	char	**fields;
	size_t	i;

	fields = field_splitting(word);
	i = 0;
	while (fields[i])
	{
		if (word_is_file_pattern(word))
		{
			quote_removal(fields[i], ft_strlen(fields[i]));
			expand_asterisk_into_argv(fields[i], argv);
		}
		else
		{
			quote_removal(fields[i], ft_strlen(fields[i]));
			args_append(argv, fields[i]);
		}
		i++;
	}
}

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
			read_word_into_argv(arg, &ast->simple_cmd);
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
 * Return: Return true if success or false if ambiguous error found
 */
bool	ast_expand(t_ast *ast)
{
	if (!ast)
		return (true);
	if (ast->type == AST_CONNECTOR || ast->type == AST_INVALID)
		return (true);
	if (ast->type == AST_SIMPLE_COMMAND)
		ast_expand_argv(ast);
	return (ast_expand_redirections(ast));
}
