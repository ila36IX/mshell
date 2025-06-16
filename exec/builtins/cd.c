#include "./builtins.h"

/*
 * cd - changes the current working directory
 * @ac: Number of positional given arguments
 * @av: Argumenst (target directory)
 * Return: EXIT_SUCCESS if succeeded or EXIT_FAILURE otherwise
 */
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
