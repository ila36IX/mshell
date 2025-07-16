# include "./exec.h"


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

int	exec_simple_command(t_ast *ast)
{
	int		status;
	pid_t	pid;

	if (ast == NULL)
		return (ERR_NULL);
	status = 0;
	ast_expand(ast);
	if (is_builtin(ast) == true)
		status = exec_builtin(ast);
	else
	{
		pid = fork();
		if (pid == FAIL)
			return (EXIT_FAILURE);
		if (pid == 0)
		{
			close_gates();
			status = exec_executable(ast);
			exit(status);
		}
		else
			pid_push(pid);
		status_set(status);
	}
	return (status);
}
