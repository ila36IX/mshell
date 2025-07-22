/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_fields_splitting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 06:44:42 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/21 06:44:42 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_parser.h"

void	skip_quotes(char *word, size_t *i)
{
	char	quote;

	quote = word[*i];
	(*i)++;
	while (word[*i] && word[*i] != quote)
		(*i)++;
	if (word[*i] == quote)
		(*i)++;
}

static bool	needs_field_splitting(char *word)
{
	size_t	i;

	i = 0;
	while (word && word[i])
	{
		if (word[i] == '"' || word[i] == '\'')
			skip_quotes(word, &i);
		else
		{
			if (is_whitespace(word[i]))
				return (true);
			i++;
		}
	}
	return (false);
}

static size_t	count_fields(char *word)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (word && word[i])
	{
		while (is_whitespace(word[i]))
			i++;
		while (word[i] && !is_whitespace(word[i]))
		{
			if (word[i] == '"' || word[i] == '\'')
				skip_quotes(word, &i);
			else
				i++;
		}
		j++;
	}
	return (++j);
}

static void	read_quotes_into_string(t_string *str, char *word, size_t *i)
{
	char	quote;

	if (word[*i] != '"' && word[*i] != '\'')
		return ;
	quote = word[*i];
	string_append_char(str, word[*i]);
	(*i)++;
	while (word[*i] && word[*i] != quote)
	{
		string_append_char(str, word[*i]);
		(*i)++;
	}
	if (word[*i] == quote)
	{
		string_append_char(str, word[*i]);
		(*i)++;
	}
}

static char	**allocate_fields(char *word)
{
	t_string	str;
	char		**fields;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	fields = ft_malloc(count_fields(word), sizeof(char *));
	while (word[i])
	{
		while (is_whitespace(word[i]))
			i++;
		str = string_init();
		while (word[i] && !is_whitespace(word[i]))
		{
			if (word[i] == '"' || word[i] == '\'')
				read_quotes_into_string(&str, word, &i);
			else
				string_append_char(&str, word[i++]);
		}
		if (str.buff[0])
			fields[j++] = str.buff;
	}
	fields[j] = NULL;
	return (fields);
}

char	**field_splitting(char *word)
{
	char	**fields;

	if (!needs_field_splitting(word))
	{
		fields = ft_malloc(2, sizeof(char *));
		fields[0] = word;
		fields[1] = NULL;
		return (fields);
	}
	else
		return (allocate_fields(word));
}
