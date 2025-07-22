#include "./exec.h"

int	get_pipe_in(void)
{
	return (pipe_in_act(GET, 0));
}

int	get_pipe_out(void)
{
	return (pipe_in_act(GET, 0));
}

int	get_pipe_count(void)
{
	return (pipe_count_act(GET, 0));
}

int	get_current_pipe(void)
{
	return (current_pipe_act(GET, 0));
}
