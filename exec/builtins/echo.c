# include "../../libft/libft.h"
# include "../../includes.h"


/**
	* echo - Mimics the behavior of the echo command
	* writes the given arguemnt/text to STDOUT
	* @ac: Number of provided arguments
	* @av: Args provided
	* Return: Number of bytes written or EXIT_FAILURE (1) instead
*/

bool	is_option(const char *opt)
{
	int	i;

	if (opt == NULL)
		return (ERR_NULL);
	i = 0;
	if (opt[i++] !=  '-')
		return (false);
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	ft_echo(int ac, char **av)
{
	int	i;
	bool	newline;

	if (av == NULL)
		return (printf("NULL arguments\n"), ERR_NULL);
	if (ac == 1)
	{
		printf("\n");
		return (SUCCESS);
	}
	i = 1;
	newline = true;
	while (av[i] && is_option(av[i]) == true)
	{
		newline = false;
		i++;
	}
	while (av[i])
	{
		printf("%s", av[i]);
		if (av[i + 1])
			printf(" ");
		i++;
	}
	if (newline == true)
		printf("\n");
	return (SUCCESS);

}
