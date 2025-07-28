/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 01:38:04 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/28 01:38:05 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include "../libft/libft.h"
#define PIPE_SIZE 2

int	handle_single_command(t_ast *ast)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (ast->type == AST_SUBSHELL)
	{
		pid = fork();
		if (pid == FAIL)
			return (status_set(ERR_NULL), ERR_NULL);
		if (pid == 0)
		{
			if (ast_expand(ast) == false || setup_redirections(ast) != SUCCESS)
				return (status_set(ERR_NULL), ERR_NULL);
			exec(ast->subshell);
			ft_clean();
			exit(status_get());
		}
		else
			waitpid(pid, &status, 0);
		return (status_set(WEXITSTATUS(status)), WEXITSTATUS(status));
	}
	if (ast_expand(ast) == false
		|| setup_redirections(ast) != SUCCESS)
		return (status_set(ERR_NULL), ERR_NULL);
	exec_simple_command(ast);
	return (status_get());
}

static t_ast	*handle_single_node(t_ast *ast,
		int **pipes, int *count, int number_of_nodes)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (ast_expand(ast) == false
			|| setup_pipes(*count, pipes, number_of_nodes))
			return (status_set(ERR_NULL), NULL);
		if (ast->type != AST_CONNECTOR)
			if (setup_redirections(ast) != SUCCESS)
				exit(ERR_NULL);
		if (ast->type == AST_SIMPLE_COMMAND)
			status = exec_simple_command(ast);
		else if (ast->type == AST_SUBSHELL)
			status = exec(ast->subshell);
		ft_clean();
		exit(status_get());
	}
	pid_push(pid);
	*count += 1;
	return (ast);
}

t_ast	*execute_pipeline(t_ast *ast)
{
	int		number_of_nodes;
	int		**pipes;
	int		count;

	if (ast == NULL)
		return (ast);
	count = 0;
	pipes = init_pipes(&number_of_nodes, ast);
	if (number_of_nodes == 1)
		return (handle_single_command(ast), ast->next);
	while (ast && is_logical_connector(ast) == false)
	{
		if (ast->type != AST_CONNECTOR)
			ast = handle_single_node(ast, pipes, &count, number_of_nodes);
		ast = ast->next;
	}
	close_all_pipes(pipes, number_of_nodes - 1);
	status_set(pid_wait_all());
	return (ast);
}

int	exec(t_ast *ast)
{
	if (ast == NULL)
		return (ERR_NULL);
	while (ast)
	{
		if (ast->type == AST_SIMPLE_COMMAND
			|| ast->type == AST_SUBSHELL)
			ast = execute_pipeline(ast);
		else if (ast->type == AST_CONNECTOR)
			ast = exec_connector(ast);
		else if (ast)
			ast = ast->next;
	}
	dup2(get_pipe_in(), STDIN_FILENO);
	dup2(get_pipe_out(), STDOUT_FILENO);
	close(get_pipe_in());
	close(get_pipe_out());
	return (status_get());
}
