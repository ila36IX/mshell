/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:14:24 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/26 22:06:28 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include "../libft/libft.h"

int	pipe_in_act(int action, int hold)
{
	static int	pipe_in;

	if (action == GET)
		return (pipe_in);
	if (action == SET)
		pipe_in = hold;
	return (pipe_in);
}

int	pipe_out_act(int action, int hold)
{
	static int	pipe_out;

	if (action == GET)
		return (pipe_out);
	if (action == SET)
		pipe_out = hold;
	return (pipe_out);
}

int	current_pipe_act(int action, int hold)
{
	static int	current_pipe;

	if (action == GET)
		return (current_pipe);
	if (action == SET)
		current_pipe = hold;
	return (current_pipe);
}

int	pipe_count_act(int action, int hold)
{
	static int	pipe_count;

	if (action == GET)
		return (pipe_count);
	if (action == SET)
		pipe_count = hold;
	return (pipe_count);
}

int	**pipes_act(int action)
{
	static int	**pipes;
	int			i;

	if (action == SET)
	{
		pipe_count_act(SET, 0);
		current_pipe_act(SET, 0);
		pipes = NULL;
		return (NULL);
	}
	if (pipes == NULL)
	{
		pipes = ft_malloc(sizeof(int *), MAX_PIPES_COUNT);
		if (!pipes)
			exit(0);
		i = 0;
		while (i < MAX_PIPES_COUNT)
		{
			pipes[i] = ft_malloc(sizeof(int), PIPE_SIZE);
			if (!pipes[i])
				exit(0);
			i++;
		}
	}
	return (pipes);
}
