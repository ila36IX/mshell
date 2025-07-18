# include "../../includes.h"
#include "../status.h"
# include "./environ.h"



/*
 * cd - changes the current working directory
 * @ac: Number of positional given arguments
 * @av: Argumenst (target directory)
 * Return: EXIT_SUCCESS if succeeded or EXIT_FAILURE otherwise
 */
int	ft_cd(int ac, char **av)
{
	int	status;
	char	newdir[MAX_WD_SIZE];


	if (av == NULL)
		return (ERR_NULL);
	if (ac == 1)
		av[1] = (char *)environ_get("HOME");
	if (ac > 2)
	{
		dprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		status_set(EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (getcwd(newdir, MAX_WD_SIZE) ==  NULL)
		return (EXIT_FAILURE);
	if (av[1] && ft_strlen(av[1]) == 0)
	{
		printf("%s\n", newdir);
		return (EXIT_SUCCESS);
	}
	status = chdir(av[1]);
	if (status != EXIT_SUCCESS)
	{
		status_set(EXIT_FAILURE);
		dprintf(STDERR_FILENO, " %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	if (getcwd(newdir, MAX_WD_SIZE) ==  NULL)
		return (EXIT_FAILURE);
	environ_set("PWD", newdir);
	return (SUCCESS);
}
