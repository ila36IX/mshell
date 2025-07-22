/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_expand_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 18:04:58 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/22 18:04:58 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ast_parser.h"

static bool	wildcard_between_quotes(char *word, int *i)
{
	char	quote;

	quote = word[*i];
	(*i)++;
	while (word[*i] && word[*i] != quote)
	{
		if (word[*i] == '*')
			return (true);
		(*i)++;
	}
	if (word[*i] == quote)
		(*i)++;
	return (false);
}

bool	word_is_file_pattern(char *word)
{
	int		i;
	char	is_pattern;

	i = 0;
	is_pattern = false;
	while (word[i])
	{
		if (word[i] == '"' || word[i] == '\'')
		{
			if (wildcard_between_quotes(word, &i))
				return (false);
		}
		else if (word[i] == '*')
		{
			is_pattern = true;
			i++;
		}
		else
			i++;
	}
	return (is_pattern);
}
