# include "./exec.h"
# include "./status.h"
# include "./builtins/environ.h"
# include "../libft/libft.h"
# include <dirent.h>

# define ERR_NOT_FOUND 127

char	*get_full_name(char *name)
{
	char	**list;
	const char	*env;
	char	*final_path;
	int	i;

	if (!name)
		return (NULL);
	if (opendir(name) != NULL)
	{
		if (ft_strchr(name, '/'))
		{
			status_set(126);
			dprintf(STDERR_FILENO, "minishell: %s: Is a directory\n", name);
		}
		else
		{
			status_set(127);
			dprintf(STDERR_FILENO, "%s: command not found\n", name);
		}
		return (NULL);
	}
	if (access(name, F_OK | X_OK) == 0)
		return (name);
	else if (access(name, F_OK) == 0 && ft_strchr(name, '/'))
	{
		status_set(126);
		dprintf(STDERR_FILENO, "minishell: %s: Permission denied\n", name);
		return (NULL);
	}
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
	if (ft_strchr(name, '/'))
		dprintf(STDERR_FILENO, "%s: No such file or directory\n", name);
	else
		dprintf(STDERR_FILENO, "%s: command not found\n", name);
	status_set(ERR_NOT_FOUND);
	return (NULL);
}

int exec_executable(t_ast *ast)
{
	char	**av;
	int	ac;
	int	status;
	char	*cmd_name;
	char	**envp;

	if (ast == NULL)
		return (ERR_NULL);
	if (ast->simple_cmd.argv == NULL)
		return (ERR_NULL);
	av = ast->simple_cmd.argv;
	ac = ast->simple_cmd.argc;
	status = 0;
	if (ft_strlen(av[0]) == 0)
		return (status);
	cmd_name = get_full_name(av[0]);
	envp = environ_array_execve();
	if (execve(cmd_name, av, envp) == FAIL)
		return (EXIT_FAILURE);

	return (status);
}
