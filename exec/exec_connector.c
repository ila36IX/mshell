# include "./exec.h"
# include "./status.h"

/* int exec_connected(t_ast *ast, int pipe_out)
{
	pid_t	pid;

	if (!ast)
		return (FAIL);
	if (ast->connector == CONNECTOR_OR)
	{
		if (status_get() == 0)
			return (SUCCESS);
		else
		{
			pid = fork();
			if (pid == FAIL)
				return (FAIL);
			if (pid == 0)
				exec_simple_cmd(ast->next, -1, pipe_out);
		}
	}
	else if (ast->connector == CONNECTOR_AND)
	{
		if (status_get() != 0)
			return (FAIL);
		else
		{
			pid = fork();
			if (pid == FAIL)
				return (FAIL);
			if (pid == 0)
				exec_simple_cmd(ast->next, -1, pipe_out);
		}
	}
	return (SUCCESS);
} */

