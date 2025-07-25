/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_curr_dir_files.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 08:05:43 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/24 08:05:43 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_parser.h"

bool	get_sorted_files(char **nodes, int *size, char *pattern)
{
	DIR				*dir_obj;
	struct dirent	*dir;

	dir_obj = opendir(".");
	*size = 0;
	if (!dir_obj)
		return (false);
	while (dir_obj)
	{
		dir = readdir(dir_obj);
		if (!dir)
			break ;
		if (wildcmp(dir->d_name, pattern))
		{
			nodes[*size] = ft_strdup(dir->d_name);
			*size += 1;
		}
		if (*size > MAX_FILES_IN_DIR - 1)
			break ;
	}
	sort_filenames(nodes, *size);
	closedir(dir_obj);
	return (dir_obj);
}

bool	expand_asterisk_into_argv(char *pattern, t_simple_cmd *argv)
{
	char	*nodes[MAX_FILES_IN_DIR];
	int		size;
	int		i;
	int		j;

	get_sorted_files(nodes, &size, pattern);
	i = 0;
	j = 0;
	while (i < size)
	{
		if ((pattern[0] == '.' && nodes[i][0] == '.') || (pattern[0] != '.'
				&& nodes[i][0] != '.'))
		{
			args_append(argv, nodes[i]);
			j++;
		}
		i++;
	}
	if (j == 0)
	{
		args_append(argv, pattern);
		return (true);
	}
	return (true);
}

char	*expand_asterisk_for_redir(char *pattern)
{
	char	*nodes[MAX_FILES_IN_DIR];
	int		size;
	int		i;
	int		j;
	char	*file;

	get_sorted_files(nodes, &size, pattern);
	i = 0;
	j = 0;
	while (i < size)
	{
		if ((pattern[0] == '.' && nodes[i][0] == '.') || (pattern[0] != '.'
				&& nodes[i][0] != '.'))
		{
			file = nodes[i];
			j++;
		}
		i++;
	}
	if (size == 0)
		return (pattern);
	if (j == 1)
		return (file);
	return (NULL);
}
