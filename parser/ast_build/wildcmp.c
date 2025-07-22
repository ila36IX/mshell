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
#include <dirent.h>
#define SORTED_CHARS " !\"#%&'()*+,:;<=>?@[\\]^_`{|}~$"
#define MAX_FILES_IN_DIR 4242

bool wildcmp(char *s, size_t ssz, char *p, size_t psz)
{
	int i;

	if (psz == 0) 
		return (ssz == 0);
	if (p[0] == '*') 
	{
		i = 0;
		while (i <= ssz)
		{
			if (wildcmp(s + i, ssz - i, p + 1, psz - 1))
				return (true);
			i++;
		}
		return (false);
	}
	else if (ssz > 0 && s[0] == p[0])
	{
		return (wildcmp(s + 1, ssz - 1, p + 1, psz - 1));
	}
	return (false);
}

unsigned int char_lexecal_rank(char c)
{
	int i;

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

int lexical_strcmp(const char *a, const char *b)
{
	int i = 0;
	while (a[i] && b[i])
	{
		if (a[i] != b[i])
			return (char_lexecal_rank(a[i]) - char_lexecal_rank(b[i]));

		i++;
	}
	return (char_lexecal_rank(a[i]) - char_lexecal_rank(b[i]));
}

void sort_strings(char **arr, int n)
{
	char *temp;
	int i;
	int j;

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

DIR *get_sorted_files(char **nodes, int *size, char *pattern, size_t pattern_size)
{	
	DIR	      *dir_obj;
	struct dirent *dir;

	dir_obj = opendir(".");
	*size = 0;
	while (dir_obj)
	{
		dir = readdir(dir_obj);
		if (!dir)
			break ;
		if (wildcmp(dir->d_name, ft_strlen(dir->d_name), pattern, pattern_size))
		{
			nodes[*size] = dir->d_name;
			*size += 1;
		}
		if (*size > MAX_FILES_IN_DIR - 1)
			break ;
	}
	sort_strings(nodes, *size);
	return (dir_obj);
}

bool expand_asterisk_into_argv(char *pattern, t_simple_cmd *argv)
{
	char *nodes[MAX_FILES_IN_DIR];
	int size;
	int i;
	DIR	      *dir_obj;

	dir_obj = get_sorted_files(nodes, &size, pattern, ft_strlen(pattern));
	if (!dir_obj)
		return (false);
	i = 0;
	while (i < size)
	{
		if (pattern[0] == '.' && nodes[i][0] == '.')
			args_append(argv, ft_strdup(nodes[i]));
		if (pattern[0] != '.' && nodes[i][0] != '.')
			args_append(argv, ft_strdup(nodes[i]));
		printf(".");
		i++;
	}
	closedir(dir_obj);
	if (size == 0)
	{
		args_append(argv, pattern);
		return (true);
	}
	return (true);
}
