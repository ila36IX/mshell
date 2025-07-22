/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_sort_files_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:58:42 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/22 17:58:42 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast_parser.h"

static unsigned int	char_alpha_rank(char c)
{
	size_t	i;

	if (c >= 'a' && c <= 'z')
		return (300 + (c - 'a') * 2);
	if (c >= 'A' && c <= 'Z')
		return (300 + (c - 'A') * 2 + 1);
	if (ft_isdigit(c))
		return (200 + c - '0');
	i = 0;
	while (i < ft_strlen(SORTED_CHARS))
	{
		if (SORTED_CHARS[i] == c)
			return (i + 100);
		i++;
	}
	return (c);
}

static int	lexical_strcmp(const char *a, const char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i])
	{
		if (a[i] != b[i])
			return (char_alpha_rank(a[i]) - char_alpha_rank(b[i]));
		i++;
	}
	return (char_alpha_rank(a[i]) - char_alpha_rank(b[i]));
}

void	sort_filenames(char **arr, int n)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - i - 1)
		{
			if (lexical_strcmp(arr[j], arr[j + 1]) > 0)
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
