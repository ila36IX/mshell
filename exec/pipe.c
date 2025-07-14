# include "./exec.h"


int	pipe_in;
int	pipe_out;

int	pipe_init(void)
{
	pipe_in = dup(STDIN_FILENO);
	pipe_out = dup(STDOUT_FILENO);
	if (pipe_in != FAIL || pipe_out != FAIL)
		return (SUCCESS);
	return (EXIT_FAILURE);
}

int	pipe_get_in(void)
{
	return (pipe_in);
}

int	pipe_get_out(void)
{
	return (pipe_out);
}

int	pipe_setall(t_ast *ast, int pipes[MAX_PIPES_COUNT][PIPE_SIZE])
{
	int		count;

	if (ast == NULL)
		return (ERR_NULL);
	count = 0;
	while (ast)
	{
		if (ast->type != AST_SIMPLE_COMMAND && is_pipe(ast) == false)
			break ;
		if (is_pipe_next(ast) == true)
		{
			pipe(pipes[count]);
			count += 1;
		}
		ast = ast->next;
	}
	return (count);
}
