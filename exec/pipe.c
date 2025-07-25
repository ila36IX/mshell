/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:13:53 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:14:07 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

int	pipe_init(void)
{
	int	i;
	int	**pipes;

	pipes = pipes_act(GET, NULL);
	pipe_in_act(SET, dup(STDIN_FILENO));
	pipe_out_act(SET, dup(STDOUT_FILENO));
	if (get_pipe_in() != FAIL || get_pipe_out() != FAIL)
		return (SUCCESS);
	i = 0;
	while (i < MAX_PIPES_COUNT)
	{
		pipes[i][0] = -1;
		pipes[i][1] = -1;
		i++;
	}
	return (EXIT_FAILURE);
}

int	init_gates(t_ast *ast)
{
	int	**pipes;

	pipes = pipes_act(GET, NULL);
	set_pipe_count(0);
	set_current_pipe(0);
	if (ast == NULL)
		return (FAIL);
	while (ast)
	{
		if (is_pipe(ast))
		{
			if (pipe(pipes[get_pipe_count()]) == FAIL)
				return (FAIL);
			set_pipe_count(get_pipe_count() + 1);
		}
		ast = ast->next;
	}
	return (get_pipe_count());
}

int	setup_gates(t_ast *ast, int node_count)
{
	int	g_pipe_input;
	int	g_pipe_output;
	int	**pipes;

	pipes = pipes_act(GET, NULL);
	g_pipe_input = -1;
	g_pipe_output = -1;
	pipe_init();
	if (node_count == 0)
	{
		if (is_pipe_next(ast))
		{
			g_pipe_output = pipes[get_current_pipe()][1];
			set_current_pipe(get_current_pipe() + 1);
		}
	}
	else
	{
		g_pipe_input = pipes[get_current_pipe() - 1][0];
		if (is_pipe_next(ast))
		{
			g_pipe_output = pipes[get_current_pipe()][1];
			set_current_pipe(get_current_pipe() + 1);
		}
	}
	if (setup_fds(ast, g_pipe_input, g_pipe_output))
		return (status_set(1), EXIT_FAILURE);
	return (0);
}

int	restore_gates(void)
{
	int	status;

	status = 0;
	dup2(get_pipe_in(), STDIN_FILENO);
	dup2(get_pipe_out(), STDOUT_FILENO);
	return (status);
}

int	close_gates(void)
{
	int	status;
	int	i;
	int	g_pipe_count;
	int	**pipes;

	pipes = pipes_act(GET, NULL);
	g_pipe_count = get_pipe_count();
	status = 0;
	i = 0;
	while (i < g_pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	return (status);
}
