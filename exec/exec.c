#include "./exec.h"
#include "../libft/libft.h"
#define PIPE_SIZE 2

int	handle_single_command(t_ast *ast)
{
	pid_t	pid;

	if (ast->type == AST_SUBSHELL)
	{
		pid = fork();
		if (pid == 0)
		{
			ast_expand(ast);
			if (setup_redirections(ast) != SUCCESS)
				return (ERR_NULL);
			exec(ast->subshell);
			exit(0);
		}
		else
			waitpid(pid, NULL, 0);
		return (SUCCESS);
	}
	ast_expand(ast);
	if (setup_redirections(ast) != SUCCESS)
		return (ERR_NULL);
	/* dprintf(get_pipe_out(), "Setting the redirections succeeded\n"); */
	exec_simple_command(ast);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (SUCCESS);
}

t_ast	*execute_pipeline(t_ast *ast)
{
	int		number_of_nodes;
	int		**pipes;
	pid_t	pid;
	int		count;

	if (ast == NULL)
		return (ast);
	count = 0;
	pipes = init_pipes(&number_of_nodes, ast);
	if (number_of_nodes == 1)
	{
		/* dprintf(get_pipe_out(), "Handling a single command\n"); */
		handle_single_command(ast);
		return (ast->next);
	}
	while (ast && is_logical_connector(ast) == false)
	{
		if (ast->type != AST_CONNECTOR)
		{
			pid = fork();
			if (pid == 0)
			{
				ast_expand(ast);
				setup_pipes(count, pipes, number_of_nodes);
				if (ast->type != AST_CONNECTOR)
					if (setup_redirections(ast) != SUCCESS)
						return (NULL);
				if (ast->type == AST_SIMPLE_COMMAND)
					exec_simple_command(ast);
				else if (ast->type == AST_SUBSHELL)
				{
					exec(ast->subshell);
				}
				exit(0);
			}
		}
		if (ast->type != AST_CONNECTOR)
			count += 1;
		ast = ast->next;
	}
	close_all_pipes(pipes, number_of_nodes - 1);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (ast);
}

int	exec(t_ast *ast)
{
	int		node_count;

	if (ast == NULL)
		return (ERR_NULL);
	set_pipe_in(dup(STDIN_FILENO));
	set_pipe_out(dup(STDOUT_FILENO));
	while (ast)
	{
		if (ast->type == AST_SIMPLE_COMMAND
			|| ast->type == AST_SUBSHELL)
			ast = execute_pipeline(ast);
		else if (ast->type == AST_CONNECTOR)
			ast = exec_connector(ast, &node_count);
		if (ast)
			ast = ast->next;
	}
	dup2(get_pipe_in(), STDIN_FILENO);
	dup2(get_pipe_out(), STDOUT_FILENO);
	close(get_pipe_in());
	close(get_pipe_out());
	return (status_get());
}
