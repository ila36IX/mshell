/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:46:57 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/05 18:14:01 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../exec/status.h"
#include "ast_parser.h"

/**
 * environ_get_ncstr - get environment varaible of string using its size
 *
 * @s: string identifies by its size, not by null terminator at the end
 * @size: size of s
 *
 * Return: Pointer of string from the environ varaible
 */
const char	*environ_get_ncstr(const char *s, size_t size)
{
	t_string	string;
	const char	*value;

	value = NULL;
	string = string_init();
	string_append_str(&string, s, size);
	value = environ_get(string.buff);
	return (value);
}

/**
 * expand_var - get the vlue of the next varaible, and add append is in the end
 * of @str
 *
 * @str: string buffer tp append to it
 * @s: string which currently getttng expanded
 * @curr_idx: the index of the start of varible name
 * @size: size of @s
 *
 * Return: size of which s moved
 */
static size_t	expand_var(t_string *str, const char *s, size_t curr_idx,
		size_t size)
{
	size_t		i;
	const char	*s_pos;
	const char	*value;

	s_pos = &s[curr_idx];
	i = 0;
	while (curr_idx < size && (ft_isalnum(s[curr_idx]) || s[curr_idx] == '_'))
	{
		i++;
		curr_idx++;
	}
	if (i == 0)
		return (0);
	value = environ_get_ncstr(s_pos, i);
	serialize_and_append(str, value);
	return (i);
}

void	string_append_nbr(t_string *s, int nb)
{
	unsigned int	n;

	if (nb < 0)
	{
		n = nb * -1;
		string_append_char(s, '-');
	}
	else
		n = nb;
	if (n > 9)
		string_append_nbr(s, n / 10);
	string_append_char(s, n % 10 + '0');
}

/**
 * expand_string - expand the contetn of str if its expandeble
 *
 * @str: string to expand
 * @size: size of str, null is no expantec
 *
 * Return: Pointer to new string that has been expanded, call quote_removal
 * later to remove quotes
 */
char	*expand_string(const char *str, size_t size)
{
	size_t		i;
	t_string	s;

	s = string_init();
	i = 0;
	while (str && i < size)
	{
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '_'))
		{
			i++;
			i += (expand_var(&s, str, i, size));
		}
		else if (str[i] == '$' && str[i + 1] == '?')
			i = (string_append_nbr(&s, status_get()), i + 2);
		else if (str[i] == '\'')
		{
			string_append_char(&s, str[i++]);
			while (i < size && str[i] != '\'')
				string_append_char(&s, str[i++]);
			string_append_char(&s, str[i++]);
		}
		else
			string_append_char(&s, str[i++]);
	}
	return (s.buff);
}
