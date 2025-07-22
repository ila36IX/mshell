# include "./exec.h"
# define PIPE_SIZE 2

static t_ast	*exec_connector(t_ast *ast, int *node_count)
{
	t_connector	connector;

	if (ast == NULL)
		return (NULL);
	connector = ast->connector;
	if (connector == CONNECTOR_AND)
	{
		while (waitpid(-1, NULL, 0) > 0)
			;
		*node_count = 0;
		if (status_get() == SUCCESS)
			return (ast);
		else
				return (ast->next);
	}
	if (connector == CONNECTOR_OR)
	{
		pid_wait_all();
		*node_count = 0;
		if (status_get() != SUCCESS)
			return (ast);
		else
			return (ast->next);
	}
	else if (connector == CONNECTOR_PIPE)
		return (ast);
	return (NULL);
}

int	exec(t_ast *ast)
{
	int		status;
	pid_t	subshell;
	int		node_count;

	if (ast == NULL)
		return (ERR_NULL);
	status =  0;
	node_count = 0;
	init_gates(ast);
	pid_init();
	while (ast)
	{
		if (ast->type != AST_CONNECTOR)
			ast_expand(ast);
		if (ast->type == AST_SIMPLE_COMMAND && ast->simple_cmd.argv[0] != NULL)
		{
			if (setup_gates(ast, node_count) == SUCCESS)
				exec_simple_command(ast);
			node_count += 1;
		}
		if (ast->type == AST_SUBSHELL)
		{
			subshell = fork();
			if (subshell == FAIL)
				return (status_get());
			if (subshell  == 0)
			{
				signal(SIGINT,child_signal_handler);
				close_gates();
				if (setup_gates(ast, node_count) != SUCCESS)
					status = exec(ast->subshell);
				exit(status);
			}
			else
				waitpid(subshell, &status, -1);
			node_count += 1;
		}
		else if (ast->type == AST_CONNECTOR)
			ast = exec_connector(ast, &node_count);
		restore_gates();
		if (ast)
			ast = ast->next;
	}
	close_gates();
	while (waitpid(-1, &status, 0) > 0)
		;
	return (status_get());
}
