#include "./exec.h"
#include "../includes.h"
#include "../libft/libft.h"
#include "./builtins/builtins.h"

int	exec_builtin(t_ast *ast)
{
	char	**av;
	int		ac;
	int		pid;
	int		status;

	if (ast == NULL)
		return (ERR_NULL);
	if (ast->simple_cmd.argv == NULL)
		return (ERR_NULL);
	pid = 0;
	status = 0;
	if (is_pipe_next(ast) == true)
		pid = fork();
	if (pid == 0)
	{
		av = ast->simple_cmd.argv;
		ac = ast->simple_cmd.argc;
		if (ft_strcmp(av[0], "echo") == SUCCESS)
			status = ft_echo(ac, av);
		if (ft_strcmp(av[0], "cd") == SUCCESS)
			status = ft_cd(ac, av);
		if (ft_strcmp(av[0], "pwd") == SUCCESS)
			status = ft_pwd(ac, av);
		if (ft_strcmp(av[0], "export") == SUCCESS && !is_pipe_next(ast))
			status = ft_export(ac, av);
		if (ft_strcmp(av[0], "unset") == SUCCESS)
			status = ft_unset(ac, av);
		if (ft_strcmp(av[0], "env") == SUCCESS)
			status = ft_env(ac, av);
		if (ft_strcmp(av[0], "exit") == SUCCESS)
			status = ft_exit(ac, av);
		if (is_pipe_next(ast) == true)
			exit(status);
		else
			return (status);
	}
	else
		pid_push(pid);
	return (SUCCESS);
}
