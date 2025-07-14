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

static int	link_pipe(t_ast *ast,
		int pipes[MAX_PIPES_COUNT][PIPE_SIZE], int command_count)
{
			if (command_count == 0)
			{
				if (is_pipe_next(ast))
					setup_fds(ast, -1, pipes[command_count][1]);
				else
					setup_fds(ast, -1, -1);
			}
			else if (is_pipe_next(ast))
					setup_fds(ast, pipes[command_count - 1][0], pipes[command_count][1]);
			else
				setup_fds(ast, pipes[command_count - 1][0], -1);
			return (SUCCESS);
}


int	exec_simple_command(t_ast *ast)
{
	int		status;
	int 	pipes[MAX_PIPES_COUNT][PIPE_SIZE];
	int		command_count;
	int		pipe_count;
	int		saved_stdin;
	int		saved_stdout;
	pid_t	pid;

	if (ast == NULL)
		return (ERR_NULL);
	status = 0;
	command_count = 0;
	pipe_count = pipe_setall(ast, pipes);
	while (ast)
	{
		if (ast->type != AST_SIMPLE_COMMAND && !is_pipe(ast))
			break;
		if (ast->type == AST_SIMPLE_COMMAND)
		{
			ast_expand(ast);
			saved_stdin = dup(STDIN_FILENO);
			saved_stdout = dup(STDOUT_FILENO);
			if (is_builtin(ast) == true)
			{
				link_pipe(ast, pipes, command_count);
				status = exec_builtin(ast);
			}
			else
			{
				pid = fork();
				if (pid == FAIL)
					return (EXIT_FAILURE);
				if (pid == 0)
				{
					link_pipe(ast, pipes, command_count);
					for (int i  = 0; i < pipe_count; i++)
					{
						close(pipes[i][0]);
						close(pipes[i][1]);
					}
					status = exec_executable(ast);
					exit(status);
				}
			}
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdin);
			close(saved_stdout);
			command_count += 1;
		}
		ast = ast->next;
	}
	for (int i = 0; i < pipe_count; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (status);
}
