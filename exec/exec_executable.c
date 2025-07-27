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

char	*get_full_name(char *name)
{
	char		*final_path;

	if (access(name, F_OK | X_OK) == 0 && opendir(name) == NULL)
		return (name);
	final_path = get_from_env(name);
	if (final_path)
		return (final_path);
	dprintf(STDERR_FILENO, "%s: command not found\n", name);
	status_set(ERR_NOT_FOUND);
	return (NULL);
}

int	exec_executable(t_ast *ast)
{
	char	**av;
	int		ac;
	char	*cmd_name;
	char	**envp;

	if (ast == NULL)
		return (ERR_NULL);
	if (ast->simple_cmd.argc == 0)
		return (ERR_NULL);
	av = ast->simple_cmd.argv;
	ac = ast->simple_cmd.argc;
	cmd_name = get_full_name(av[0]);
	envp = environ_array_execve();
	if (execve(cmd_name, av, envp))
		status_set(errno);
	return (status_get());
}
