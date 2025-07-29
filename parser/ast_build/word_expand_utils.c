/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expand_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 06:09:24 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/29 06:09:24 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_parser.h"

/**
 * quote_removel_serialize - serialize quote back after after removing quotes
 */
static void	replace_quote_deserializer(char *str, size_t *pi, size_t *pj)
{
	size_t	i;
	size_t	j;

	i = *pi;
	j = *pj;
	if (str[i] == SINGLE_QUOTE_SERIALIZER)
	{
		str[i] = '\'';
		i++;
		j++;
	}
	else if (str[i] == DOUBLE_QUOTE_SERIALIZER)
	{
		str[i] = '"';
		i++;
		j++;
	}
	*pi = i;
	*pj = j;
}

/**
 * remove_enclosed_quotes - Remove the quote and its closing quote
 */
static void	remove_enclosed_quotes(char *str, size_t *pi, size_t *pj,
		size_t size)
{
	char	quote;
	size_t	i;
	size_t	j;

	i = *pi;
	j = *pj;
	quote = str[i++];
	while (i < size && str[i] != quote)
		str[j++] = str[i++];
	if (i < size)
		i++;
	i++;
	*pi = i;
	*pj = j;
}

/**
 * quote_removal - remove quotes from string
 *
 * @str: string in which to remove " or '
 * @size: size of the string, null termination is not expected
 *
 * Return: True if the string has qoutes
 */
bool	quote_removal(char *str, size_t size)
{
	size_t	i;
	size_t	j;
	bool	is_quoted;

	i = 0;
	j = 0;
	is_quoted = false;
	while (str && i < size)
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			is_quoted = true;
			remove_enclosed_quotes(str, &i, &j, size);
		}
		else if (str[i] == SINGLE_QUOTE_SERIALIZER
			|| str[i] == DOUBLE_QUOTE_SERIALIZER)
			replace_quote_deserializer(str, &i, &j);
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
	return (is_quoted);
}

/*
 * cstr_contains_quote - Check if string ending with \0 is containing quote
 */
bool	cstr_contains_quote(const char *value)
{
	size_t	i;

	i = 0;
	while (value && value[i])
	{
		if (value[i] == '"' || value[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

/**
 * serialize_and_append - add value in the end str and make sure to replace
 * qoutes that not meant to be syntactical (quotes from value after expanding)
 */
bool	serialize_and_append(t_string *str, const char *value)
{
	char	*tmp;
	size_t	i;

	if (value && cstr_contains_quote(value))
	{
		tmp = ft_strdup(value);
		i = 0;
		while (tmp[i])
		{
			if (tmp[i] == '\'')
				tmp[i] = SINGLE_QUOTE_SERIALIZER;
			else if (tmp[i] == '"')
				tmp[i] = DOUBLE_QUOTE_SERIALIZER;
			i++;
		}
		string_append_cstr(str, tmp);
	}
	else
		string_append_cstr(str, value);
	return (false);
}
