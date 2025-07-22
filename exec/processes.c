#include "./exec.h"
#include "../libft/libft.h"

#define MAX_PID_COUNT 1024

static int	*processes_get(void)
{
	static int	*processes;

	if (processes == NULL)
	{
		processes = ft_malloc(sizeof(int), MAX_PID_COUNT);
		if (processes == NULL)
			exit(0);
	}
	return (processes);
}

int	pid_count_act(int action, int hold)
{
	static int	pid_count;

	if (action == GET)
		return (pid_count);
	if (action == SET)
		pid_count = hold;
	return (pid_count);
}

int	pid_push(pid_t pid)
{
	int	*processes;

	processes = processes_get();
	if (pid == FAIL)
		return (EXIT_FAILURE);
	processes[pid_count_act(GET, 0)] = pid;
	pid_count_act(SET, pid_count_act(GET, 0) + 1);
	return (EXIT_SUCCESS);
}

int	pid_wait_all(void)
{
	int	i;
	int	status;
	int	*processes;

	i = 0;
	status = 0;
	processes = processes_get();
	while (i < pid_count_act(GET, 0))
	{
		waitpid(processes[i], &status, 0);
		if (WEXITSTATUS(status) != 0)
			return (status_set(WEXITSTATUS(status)), WEXITSTATUS(status));
		i++;
	}
	return (status);
}

int	pid_wait_last(void)
{
	int	status;
	int	*processes;

	processes = processes_get();
	if (pid_count_act(GET, 0) == 0)
		return (EXIT_FAILURE);
	status = 0;
	pid_count_act(SET, pid_count_act(GET, 0) + 1);
	waitpid(processes[pid_count_act(GET, 0)], &status, 0);
	return (status);
}
