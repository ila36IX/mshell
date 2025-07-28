/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:15:16 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:15:17 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../status.h"
#include "environ.h"
#include "../gsetters.h"
#define FAIL -1
#define ERR_NNUM_VAL 2
#define ERR_TO_MANY_ARGS 1

static int	check_multiple_args(int ac, char **av)
{
	if (ac > 2)
	{
		if (ft_atoi(av[1]) == -1 && ft_strcmp(av[1], "-1") != 0)
		{
			dprintf(STDERR_FILENO,
				"minishell: exit: %s: numeric argument required\n", av[1]);
			status_set(ERR_NNUM_VAL);
			ft_clean();
			exit(ERR_NNUM_VAL);
		}
		else
		{
			status_set(ERR_TO_MANY_ARGS);
			ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO);
			return (ERR_TO_MANY_ARGS);
		}
	}
	return (SUCCESS);
}

int	ft_exit(int ac, char **av)
{
	int	stat;
	int	val;

	stat = check_multiple_args(ac, av);
	if (stat)
		return (stat);
	if (av[1] != NULL)
	{
		val = ft_atoi(av[1]);
		if (val == FAIL && ft_strcmp(av[1], "-1"))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(av[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			ft_clean();
			exit(ERR_NNUM_VAL);
		}
		ft_clean();
		exit(val);
	}
	stat = status_get();
	ft_clean();
	exit(stat);
}
