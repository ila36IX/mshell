# include "../includes.h"
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
	redirect = setup_redirect(ast);
	if (redirect == -1)
		return (-1);
	return (SUCCESS);
}
