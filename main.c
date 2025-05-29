#include "./main.h"
#include "./memory.h"

# define UNSET(var) (void)(var);

int	main(int ac, char **av, char **envp)
{

	UNSET(ac);
	UNSET(av);
	UNSET(envp);
	char **list = ft_split(av[1], ' ');
	ft_gc_clear();

	(void)list;
	return (EXIT_SUCCESS);
}
