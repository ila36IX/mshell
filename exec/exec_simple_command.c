#include "./exec.h"
#include "../libft/libft.h"
#include <dirent.h>

int	setup_fds(t_ast *ast, int pipe_in, int pipe_out)
{
	int	redirect;

	if (ast == NULL)
		return (-1);
	if (pipe_out != -1)
	{
		if (dup2(pipe_out, STDOUT_FILENO) == -1)
			return (-1);
		if (close(pipe_out) == -1)
			return (-1);
	}
	if (pipe_in != -1)
	{
		if (dup2(pipe_in, STDIN_FILENO) == -1)
			return (-1);
		if (close(pipe_in) == -1)
			return (-1);
	}
	redirect = setup_redirections(ast);
	if (redirect == -1)
		return (-1);
	return (SUCCESS);
}

bool	is_valid_executable(t_ast *ast)
{
	char	**av;
	int		ac;
	int		status;
	char	*cmd_name;

	if (ast == NULL)
		return (ERR_NULL);
	if (ast->simple_cmd.argv == NULL)
		return (ERR_NULL);
	av = ast->simple_cmd.argv;
	ac = ast->simple_cmd.argc;
	status = 0;
	if (ft_strlen(av[0]) == 0)
		return (false);
	cmd_name = get_full_name(av[0]);
	if (cmd_name == NULL)
	{
		return (false);
	}
	return (true);
}

int	exec_simple_command(t_ast *ast)
{
	int		status;
	pid_t	pid;

	if (ast == NULL || ast->simple_cmd.argv == NULL)
		return (ERR_NULL);
	status = 0;
	if (is_builtin(ast) == true)
		status = exec_builtin(ast);
	else if (is_valid_executable(ast) == false)
		return (status_get());
	else
	{
		pid = fork();
		if (pid == FAIL)
			return (EXIT_FAILURE);
		if (pid == 0)
		{
			signal(SIGINT, child_signal_handler);
			close_gates();
			status = exec_executable(ast);
			exit(status_get());
		}
		pid_push(pid);
	}
	return (status);
}
