/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 01:17:20 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/19 01:17:20 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast_parser.h"

char *ft_strstr(char *str, char *sub, size_t subsz)
{
	size_t i;
	size_t j;

	if (*sub == '\0')
		return (str);
	i = 0;
	while (str && str[i])
	{
		j = 0;
		while (sub && str[i + j] == sub[j] && j < subsz)
			j++;
		if (j == subsz)
			return (&str[i]);
		i++;
	}
	return (NULL);
}

bool ends_with_substr(char *str, char *endian, size_t subsz)
{
	if (strlen(str) < subsz)
		return (false);
	while (str && *str)
		str++;
	str--;
	while (subsz > 0)
	{
		subsz--;
		if (*str != endian[subsz])
			return (false);
		str--;
	}
	return (true);
}


static bool _wildcmp_help(char *str, char *pattern)
{
	size_t subsz;

	while (*pattern)
	{
		while (*pattern == '*')
		{
			if (!*(++pattern))
				return (true);
		}
		subsz = 0;
		while (pattern[subsz] != '*' && pattern[subsz])
			subsz++;
		if (subsz > 0 && !pattern[subsz])
			return (ends_with_substr(str, pattern, subsz));
		str = ft_strstr(str, pattern, subsz);
		if (!str)
			return (false);
		pattern += subsz;
		str += subsz;
	}
	return (true);
}

bool wildcmp(char *str, char *pattern)
{

	while (*pattern && *pattern != '*')
	{
		if (*str != *pattern)
			return (false);
		str++;
		pattern++;
	}
	if (!*pattern && *str)
		return (false);
	if (!*pattern && !*str)
		return (true);
	return (_wildcmp_help(str, pattern));
}
