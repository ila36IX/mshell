# include "./builtins/environ.h"
#include "status.h"

static char	*get_full_pathname(char *name)
{
	char	**list;
	const char	*env;
	char	*final_path;
	int	i;

	if (!name)
		return (NULL);
	if (access(name, F_OK | X_OK) == 0)
		return (name);
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
 * Executes an executble-file command
 * @ast: Ast structure
 * Return: Exit status of the given command
 */
int	exec_precompiled(t_ast *ast)
{
	char	**envp;
	char	*cmd;

	if (!ast)
		return (EXIT_FAILURE);
	cmd = get_full_pathname(ast->simple_cmd.argv[0]);
		if (cmd == NULL)
		{
			dprintf(STDERR_FILENO, "%s: command not found\n", ast->simple_cmd.argv[0]);
			exit(NOT_FOUND);
		}
		envp = environ_array_execve();
		if (execve(cmd, ast->simple_cmd.argv, envp) == -1)
			exit(NOT_FOUND);
	return (EXIT_SUCCESS);
}
