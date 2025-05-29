#include "./main.h"
#include "./memory.h"

# define UNSET(var) (void)(var);

int	main(int ac, char **av, char **envp)
{

	UNSET(ac);
	UNSET(av);
	UNSET(envp);
	return (EXIT_SUCCESS);
}
