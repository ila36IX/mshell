# include "../../includes.h"
# include "../../libft/libft.h"
# include "../status.h"



int	quit(char **av, int ac)
{
	int	stat;

	if (ac > 2)
		return (EXIT_FAILURE);
	if (av[1] != NULL)
		exit(ft_atoi(av[1]));
	stat = status_get();
	exit(stat);
}
