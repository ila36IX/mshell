# include "../../includes.h"
# include "../../libft/libft.h"



int	quit(char **av, int ac)
{
	if (ac > 2)
		return (EXIT_FAILURE);
	if (av[1] != NULL)
		exit(ft_atoi(av[1]));
	else
		exit(0);
}
