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

int	**pipes_act(int action, int **hold)
{
	static int	**pipes;
	int			i;

	(void)hold;
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
	if (action == GET)
		return (pipes);
	return (pipes);
}
