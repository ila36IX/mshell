#include "./exec.h"
#define PIPE_SIZE 2

static int	case_simple_command(t_ast *ast, int *node_count)
{
	int		status;
	pid_t	pid;

	status = 0;
	/* dprintf(get_pipe_in(), "Simple command\n"); */
	if (*node_count || is_pipe_next(ast))
	{
		/* dprintf(get_pipe_in(), "Forking for the command in pipline\n"); */
		pid = fork();
		if (pid == 0)
		{
			if (ast->simple_cmd.argc)
			{
				status = exec_simple_command(ast, node_count);
				status_set(status);
			}
			exit(status);
		}
		else
		set_current_pipe(get_current_pipe() + 1);
	}
	else
	{
		if (ast->simple_cmd.argc)
		{
			status = exec_simple_command(ast, node_count);
			status_set(status);
		}
	}
	(*node_count) += 1;
	return (SUCCESS);
}

static int	case_subshell(t_ast *ast, int *node_count)
{
	pid_t	subshell;
	int		status;

	status = 0;
	if (ast->type == AST_SUBSHELL)
	{
		subshell = fork();
		if (subshell == FAIL)
			return (status_get());
		if (subshell == 0)
		{
			signal(SIGINT, child_signal_handler);
			if (setup_gates(ast, *node_count) != SUCCESS)
				return (ERR_NULL);
			status = exec(ast->subshell);
			exit(status);
		}
		(*node_count) += 1;
	}
	return (status);
}

int	exec(t_ast *ast)
{
	int		node_count;

	if (ast == NULL)
		return (ERR_NULL);
	node_count = 0;
	init_gates(ast);
	while (ast)
	{
		if (ast->type != AST_CONNECTOR)
			if (ast_expand(ast) == false)
				return (ERR_NULL);
		if (ast->type == AST_SIMPLE_COMMAND)
			case_simple_command(ast, &node_count);
		else if (ast->type == AST_SUBSHELL)
			case_subshell(ast, &node_count);
		else if (ast->type == AST_CONNECTOR)
			ast = exec_connector(ast, &node_count);
		restore_gates();
		if (ast)
			ast = ast->next;
	}
	close_gates();
	while(waitpid(-1, NULL, 0) > 0)
		;
	return (status_get());
}
