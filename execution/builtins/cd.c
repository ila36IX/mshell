#include "./builtins.h"

int	cd(int ac, char **av)
{
	int	status;


	if (!av || ac == 0)
		return (EXIT_FAILURE);
	if (ac > 2)
		return (EXIT_FAILURE);
	status = chdir(av[1]);
	if (status != EXIT_SUCCESS)
		perror("cd: ");
	return (status);
}
