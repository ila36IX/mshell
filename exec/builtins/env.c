#include "../../includes.h"
#include "./environ.h"

int	ft_env(int ac, char **av)
{
	if (av == NULL)
		return (ERR_NULL);
	if (ac != 1)
	{
		dprintf(STDERR_FILENO,
			"minishell: env: No arguments shall be provided\n");
		return (EXIT_FAILURE);
	}
	if (environ_print() != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
