# include "../../includes.h"
#include "../status.h"
# include "./environ.h"

int	ft_unset(int ac, char **av)
{
	int	i;

	if (ac == 1)
		return (EXIT_SUCCESS);
	if (av == NULL)
		return (ERR_NULL);
	i = 0;
	while (av[i])
	{
		environ_unset(av[i]);
		i++;
	}
	return (0);
}
