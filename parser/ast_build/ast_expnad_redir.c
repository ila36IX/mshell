/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_expnad_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 21:51:20 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/22 21:51:20 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./ast_parser.h"

static bool	word_contains_quote(t_word word)
{
	size_t	i;

	i = 0;
	while (i < word.len)
	{
		if (word.text[i] == '"' || word.text[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

static void	print_ambigous_error(t_word word)
{
	write(2, SHELL_NAME, ft_strlen(SHELL_NAME));
	write(2, ": ", 2);
	write(2, word.text, word.len);
	write(2, ": ambiguous redirect\n", 21);
}

static bool	expnad_redir_target(t_ast *ast, t_word word, int i)
{
	char	*arg;

	arg = expand_string(word.text, word.len);
	if (needs_field_splitting(arg))
	{
		print_ambigous_error(word);
		return (false);
	}
	quote_removal(arg, ft_strlen(arg));
	if (word_is_file_pattern(arg))
	{
		arg = expand_asterisk_for_redir(arg);
		if (arg)
			ast->redir[i].target = arg;
		else
		{
			print_ambigous_error(word);
			return (false);
		}
	}
	else
		ast->redir[i].target = arg;
	return (true);
}

/**
 * ast_expand_redirections - as the functions says:
 * it performs quote removal and expanding in the redirection target, if
 * redirection is herdoc, the target is the content of the herdoc and the quote
 * removel is not performed
 *
 * @ast: one node of ast
 * Return: true if success, and false if ambiguous redirection found
 */
bool	ast_expand_redirections(t_ast *ast)
{
	size_t	i;
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
				ast->redir[i].target = expand_string(target, ft_strlen(target));
		}
		else
		{
			if (!expnad_redir_target(ast, word, i))
				return (false);
		}
		i++;
	}
	return (true);
}
