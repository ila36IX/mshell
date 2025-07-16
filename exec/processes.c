# include "./exec.h"

# define MAX_PID_COUNT 1024

pid_t	processes[MAX_PID_COUNT];
static int		pid_count = 0;


void	pid_init(void)
{
	pid_count = 0;
}

int pid_push(pid_t pid)
{
	if (pid == FAIL)
		return (EXIT_FAILURE);
	processes[pid_count] = pid;
	pid_count += 1;
	return (EXIT_SUCCESS);
}

int pid_wait_all(void)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < pid_count)
	{
		waitpid(processes[i], &status, 0);
		if (WEXITSTATUS(status) !=  0)
			return (status);
		i++;
	}
	return (status);
}

int	pid_wait_last(void)
{
	int	status;

	if (pid_count == 0)
		return (EXIT_FAILURE);
	status  = 0;
	pid_count -= 1;
	waitpid(processes[pid_count], &status, 0);
	return (status);
}
