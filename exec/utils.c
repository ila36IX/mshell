# include "./exec.h"
# include "../includes.h"

/* static	int	close_pipes(int *in, int *out)
{
	if (*out != -1) {
		if (close(*out) == FAIL)
			return (FAIL);
		*out = -1;
	}
	if (*in != -1) {
		if (close(*in) == FAIL)
			return (FAIL);
		*in  = -1;
	}
	return (SUCCESS);
} */

bool	pipe_next(t_ast *ast)
{
	if (ast == NULL)
		return (false);
	if (!ast->next)
		return (false);
	if (ast->next->type == AST_CONNECTOR)
	{
		if (ast->next->connector == CONNECTOR_PIPE)
			return (true);
	}
	return (false);
}

/* int	setup_pipes(t_ast *ast)
{
	int	pipe_fd[2];

	if (ast == NULL)
		return (FAIL);
	if (pipe_next(ast) == true)
	{
		if (pipe(pipe_fd) == FAIL)
			return (FAIL);
		ast->simple_cmd.pipe_out = pipe_fd[1];
		ast->next->next->simple_cmd.pipe_in = pipe_fd[0];
	}
	else
		ast->simple_cmd.pipe_out = FAIL;
	return (SUCCESS);
} */
