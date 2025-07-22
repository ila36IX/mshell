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

bool	wildcmp(char *s, size_t ssz, char *p, size_t psz)
{
	size_t	i;

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

DIR	*get_sorted_files(char **nodes, int *size, char *pattern,
		size_t pattern_size)
{
	DIR				*dir_obj;
	struct dirent	*dir;

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
	sort_filenames(nodes, *size);
	return (dir_obj);
}

bool	expand_asterisk_into_argv(char *pattern, t_simple_cmd *argv)
{
	char	*nodes[MAX_FILES_IN_DIR];
	int		size;
	int		i;
	DIR		*dir_obj;

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
