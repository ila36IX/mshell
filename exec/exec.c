#include "./exec.h"
#include "../libft/libft.h"
#define PIPE_SIZE 2

int	handle_single_command(t_ast *ast)
{
	pid_t	pid;
	int		status;

	if (ast->type == AST_SUBSHELL)
	{
		pid = fork();
		if (pid == FAIL)
			return (status_set(ERR_NULL), ERR_NULL);
		if (pid == 0)
		{
			if (ast_expand(ast) == false)
				return (status_set(ERR_NULL), ERR_NULL);
			if (setup_redirections(ast) != SUCCESS)
				return (status_set(ERR_NULL), ERR_NULL);
			exec(ast->subshell);
			exit(status_get());
		}
		else
			waitpid(pid, &status, 0);
		return (status_set(WEXITSTATUS(status)), WEXITSTATUS(status));
	}
	if (ast_expand(ast) == false)
		return (status_set(ERR_NULL), ERR_NULL);
	if (setup_redirections(ast) != SUCCESS)
		return (status_set(ERR_NULL), ERR_NULL);
	exec_simple_command(ast);
	return (status_get());
}

t_ast	*execute_pipeline(t_ast *ast)
{
	int		number_of_nodes;
	int		**pipes;
	pid_t	pid;
	int		count;
	int		status;

	if (ast == NULL)
		return (ast);
	count = 0;
	status = 0;
	pipes = init_pipes(&number_of_nodes, ast);
	if (number_of_nodes == 1)
	{
		status = handle_single_command(ast);
		status_set(status);
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
					status = exec_simple_command(ast);
				else if (ast->type == AST_SUBSHELL)
					status = exec(ast->subshell);
				exit(status);
			}
			else
				pid_push(pid);
		}
		if (ast->type != AST_CONNECTOR)
			count += 1;
		ast = ast->next;
	}
	close_all_pipes(pipes, number_of_nodes - 1);
	waitpid(pid_get(), &status, 0);
	status_set(WEXITSTATUS(status));
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (ast);
}

int	exec(t_ast *ast)
{
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
			ast = exec_connector(ast);
		if (ast)
			ast = ast->next;
	}
	dup2(get_pipe_in(), STDIN_FILENO);
	dup2(get_pipe_out(), STDOUT_FILENO);
	close(get_pipe_in());
	close(get_pipe_out());
	return (status_get());
}
