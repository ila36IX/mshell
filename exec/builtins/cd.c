/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:08:43 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:08:44 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes.h"
#include "../status.h"
#include "./environ.h"

#define ERR_NO_PARENT "cd: No such file or directory"

int	checker(int ac, char **av)
{
	char	newdir[MAX_WD_SIZE];

	if (av == NULL)
		return (ERR_NULL);
	if (ac == 1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: no argument was provided\n");
		status_set(EXIT_FAILURE);
		return (status_get());
	}
	if (ac > 2)
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		status_set(EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	if (getcwd(newdir, MAX_WD_SIZE) == NULL)
	{
		ft_dprintf(STDERR_FILENO, " %s\n", ERR_NO_PARENT);
		return (EXIT_FAILURE);
	}
	environ_set("OLDPWD", newdir);
	return (SUCCESS);
}

/*
 * cd - changes the current working directory
 * @ac: Number of positional given arguments
 * @av: Argumenst (target directory)
 * Return: EXIT_SUCCESS if succeeded or EXIT_FAILURE otherwise
 */
int	ft_cd(int ac, char **av)
{
	int		status;
	char	newdir[MAX_WD_SIZE];

	if (checker(ac, av) != SUCCESS)
		return (EXIT_FAILURE);
	status = chdir(av[1]);
	if (status != EXIT_SUCCESS)
	{
		status_set(EXIT_FAILURE);
		ft_dprintf(STDERR_FILENO, " %s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	if (getcwd(newdir, MAX_WD_SIZE) == NULL)
		return (EXIT_FAILURE);
	environ_set("PWD", newdir);
	status_set(SUCCESS);
	return (SUCCESS);
}
