#include "./exec.h"

int	set_pipe_in(int value)
{
	return (pipe_in_act(SET, value));
}

int	set_pipe_out(int value)
{
	return (pipe_in_act(SET, value));
}

int	set_pipe_count(int value)
{
	return (pipe_count_act(SET, value));
}

int	set_current_pipe(int value)
{
	return (current_pipe_act(SET, value));
}
