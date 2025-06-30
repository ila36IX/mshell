# include "../../includes.h"
# include "../../libft/libft.h"
# include "../status.h"
# define FAIL -1
# define ERR_NNUM_VAL 2
# define TO_MANY_ARGS 1


int	quit(char **av, int ac)
{
	int	stat;
	int	val;

	if (ac > 2)
	{
		status_set(TO_MANY_ARGS);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (FAIL);
	}
	if (av[1] != NULL)
	{
		val = ft_atoi(av[1]);
		if (val == FAIL && ft_strcmp(av[1], "-1"))
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(av[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit(ERR_NNUM_VAL);
		}
		exit(val);
	}
	stat = status_get();
	exit(stat);
}
