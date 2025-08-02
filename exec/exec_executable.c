/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:13:38 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/26 22:15:16 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include "./status.h"
#include "./builtins/environ.h"
#include "../libft/libft.h"
#include <dirent.h>

#define ERR_NOT_FOUND 127
#define ERR_IS_NOT_EXECUTABLE 126

/**
 * get_from_env - Gets an executable
 * absolute path from the env
 * using the PATH var.
 * @name: Comand to get the absolute path
 * of . Ex: ls --> /bin/ls
 * Return: the absolute path
 * or  NULL if none found
 */
static char	*get_from_env(char *name)
{
	char		**list;
	const char	*env;
	char		*final_path;
	int			i;

	env = environ_get("PATH");
	if (!env)
		return (NULL);
	list = ft_split(env, ':');
	if (!list)
		return (NULL);
	i = 0;
	while (list[i])
	{
		final_path = ft_strjoin(list[i], "/");
		final_path = ft_strjoin(final_path, name);
		if (access(final_path, F_OK | X_OK) == 0)
			return (final_path);
		ft_gc_remove(final_path);
		i++;
	}
	ft_gc_remove_ft_split(list);
	return (NULL);
}

/**
 * is_file_or_directory - Checks if a given
 * string is a file or dir name
 * and handles it
 * @name: The name of the file/dir
 * @return: true if its a file/dir
 * false otherwise
 */
static bool	is_file_or_directory(char *name)
{
	DIR	*dir;

	if (name == NULL)
		return (false);
	if (ft_strchr(name, '/') == NULL)
		return (false);
	dir = opendir(name);
	if (dir != NULL)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: is a directory\n", name);
		closedir(dir);
		return (true);
	}
	closedir(dir);
	if (access(name, F_OK) == 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: Permission denied\n", name);
		return (true);
	}
	return (false);
}

/*
 * get_full_name - Gets the exec
 * command final name
 * @name: given command to handle
 * @Return: pathname if found
 * NULL otherwise
 */
char	*get_full_name(char *name)
{
	char		*final_path;
	DIR			*dir;

	dir = opendir(name);
	if (access(name, F_OK | X_OK) == 0 && dir == NULL
		&& ft_strchr(name, '/'))
		return (name);
	closedir(dir);
	if (ft_strchr(name, '/') != NULL)
	{
		ft_dprintf(STDERR_FILENO, "%s: command not found\n", name);
		return (status_set(ERR_NOT_FOUND), NULL);
	}
	final_path = get_from_env(name);
	if (final_path)
		dir = opendir(final_path);
	if (dir == NULL && access(final_path, F_OK | X_OK) == 0)
		return (final_path);
	if (dir)
		closedir(dir);
	status_set(ERR_NOT_FOUND);
	if (is_file_or_directory(name) == true)
		status_set(ERR_IS_NOT_EXECUTABLE);
	return (ft_dprintf(STDERR_FILENO,
			"%s: command not found\n", name), NULL);
}

/**
 * exec_executable - Executes an 
 * executable command
 * @ast: Node containing the command
 * data
 * Return: The exit status of the command
 */
int	exec_executable(t_ast *ast)
{
	char	**av;
	int		ac;
	char	*cmd_name;
	char	**envp;

	signal(SIGINT, child_signal_handler);
	signal(SIGQUIT, child_signal_handler);
	if (ast == NULL)
		return (ERR_NULL);
	if (ast->simple_cmd.argc == 0)
		return (SUCCESS);
	av = ast->simple_cmd.argv;
	ac = ast->simple_cmd.argc;
	cmd_name = get_full_name(av[0]);
	if (cmd_name == NULL)
		return (status_get());
	envp = environ_array_execve();
	if (execve(cmd_name, av, envp))
		status_set(errno);
	return (status_get());
}
