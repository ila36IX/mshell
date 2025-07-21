# include "./exec.h"
# define PIPE_SIZE 2

static t_ast	*exec_connector(t_ast *ast, int *node_count)
{
	t_connector	connector;
	int			status;

	if (ast == NULL)
		return (NULL);
	status = 0;
	connector = ast->connector;
	if (connector == CONNECTOR_AND)
	{
		while (waitpid(-1, &status, 0) > 0)
			;
		*node_count = 0;
		if (status_get() == SUCCESS)
			return (status_set(WEXITSTATUS(status)), ast);
		else
				return (ast->next);
	}
	if (connector == CONNECTOR_OR)
	{
		pid_wait_all();
		*node_count = 0;
		if (status_get() != SUCCESS)
			return (status_set(WEXITSTATUS(status)), ast);
		else
			return (ast->next);
	}
	else if (connector == CONNECTOR_PIPE)
		return (status_set(WEXITSTATUS(status)), ast);
	return (status_set(WEXITSTATUS(status)), NULL);
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
		{
			ast_expand(ast);
			if (setup_gates(ast, node_count) != SUCCESS)
				return (status_set(1), 1);
		}
		if (ast->type == AST_SIMPLE_COMMAND && ast->simple_cmd.argv[0] != NULL)
		{
			exec_simple_command(ast);
			node_count += 1;
		}
		if (ast->type == AST_SUBSHELL)
		{
			subshell = fork();
			if (subshell == FAIL)
				return (status);
			if (subshell  == 0)
			{
				close_gates();
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
		status_set(WEXITSTATUS(status));
	return (status_get());
}
