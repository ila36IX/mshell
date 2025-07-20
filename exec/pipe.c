# include "./exec.h"


int	pipe_in;
int	pipe_out;
int		pipes[MAX_PIPES_COUNT][PIPE_SIZE];
int		pipe_count;


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

int init_gates(t_ast *ast)
{

	pipe_count  = 0;
	if (ast == NULL)
		return (FAIL);
	while (ast)
	{
		if (is_pipe(ast))
		{
			if (pipe(pipes[pipe_count]) == FAIL)
				return (FAIL);
			pipe_count += 1;
		}
		ast = ast->next;
	}
	return (pipe_count);
}

int setup_gates(t_ast *ast, int node_count)
{
	int	status;
	int	pipe_input;
	int	pipe_output;

	status = 0;
	pipe_input = -1;
	pipe_output = -1;
	pipe_init();
	if (node_count == 0)
	{
		if (is_pipe_next(ast))
			pipe_output = pipes[node_count][1];
	}
	else {
		if (is_pipe_next(ast))
			pipe_output = pipes[node_count][1];
		pipe_input = pipes[node_count - 1][0];
	}
	status = setup_fds(ast, pipe_input, pipe_output);
	if (status == FAIL)
		return (EXIT_FAILURE);
	return (status);
}

int restore_gates(void)
{
	int	status;

	status = 0;
	dup2(pipe_get_in(), STDIN_FILENO);
	dup2(pipe_get_out(), STDOUT_FILENO);
	return (status);
}
int close_gates(void)
{
	int	status;
	int	i;

	status = 0;
	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}

	return (status);
}
