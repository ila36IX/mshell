/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:59:26 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/26 22:14:22 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

int	pipe_init(void)
{
	int	i;
	int	**pipes;

	pipes = pipes_act(GET);
	set_pipe_in(dup(STDIN_FILENO));
	set_pipe_out(dup(STDOUT_FILENO));
	if (get_pipe_in() == FAIL || get_pipe_out() == FAIL)
		return (ERR_NULL);
	i = 0;
	while (i < MAX_PIPES_COUNT)
	{
		pipes[i][0] = -1;
		pipes[i][1] = -1;
		i++;
	}
	set_pipe_count(0);
	set_current_pipe(0);
	return (EXIT_FAILURE);
}

int	init_gates(t_ast *ast)
{
	int	**pipes;
	int	pipe_count;

	pipe_init();
	pipes = pipes_act(GET);
	pipe_count = 0;
	if (pipes == NULL || ast == NULL)
		return (ERR_NULL);
	while (ast)
	{
		if (is_pipe(ast))
		{
			if (pipe(pipes[pipe_count]) == FAIL)
				return (FAIL);
			/* dprintf(get_pipe_in(), "Creating pipes with index %d\n", pipe_count); */
			pipe_count += 1;
		}
		ast = ast->next;
	}
	set_pipe_count(pipe_count);
	return (pipe_count);
}

int	setup_gates(t_ast *ast, int node_count)
{
	int	pipe_in;
	int	pipe_out;
	int	**pipes;
	int	current_pipe;

	pipes = pipes_act(GET);
	if (pipes == NULL)
		return (ERR_NULL);
	current_pipe = get_current_pipe();
	/* dprintf(get_pipe_in(), "Current pipe_count index is %d\n", current_pipe); */
	pipe_in = -1;
	pipe_out = -1;
	if (node_count)
		pipe_in = pipes[current_pipe - 1][0];
	if (is_pipe_next(ast))
		pipe_out = pipes[current_pipe][1];
	if (setup_fds(ast, pipe_in, pipe_out))
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
	int	pipe_count;
	int	**pipes;

	pipes = pipes_act(GET);
	pipe_count = get_pipe_count();
	status = 0;
	i = 0;
	/* dprintf(get_pipe_in(), "Closing gates at idx [%d]\n", pipe_count); */
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	pipes_act(SET);
	set_pipe_count(0);
	set_current_pipe(0);
	return (status);
}
