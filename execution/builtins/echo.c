# include "./builtins.h"


/**
	 * expand_write - Expands and prints a env-variable
	 * @var: Env variable key
	 * @env: linked list holding all environment variables as key.val
	 * pairs
 */
void	expand_write(char *var, t_list *env)
{
	char	*val;

	if (!var)
		return ;

	if (var[0] == '$')
	{
		val = env_get_value(var + 1, env);
		if (val)
			printf("[%s] ", val);
	}
	else
		printf("[%s] ", var);
}

/**
	* echo - Mimics the behavior of the echo command
	* writes the given arguemnt/text to STDOUT
	* @text: Text to write out
	* @:newline Option of adding a newline afterwards
	* Return: Number of bytes written or EXIT_FAILURE (1) instead
*/

int	echo(char **av, t_redirect *redir, t_list *env)
{
	int	i;
	bool	newline;

	UNSET(redir);
	if (!av)
		return (EXIT_FAILURE);
	i = 1;
	newline = true;
	while (av[i] && ft_strcmp(av[i], "-n") == 0)
	{
		newline = false;
		i++;
	}
	while (av[i])
	{
		expand_write(av[i], env);
		i++;
	}
	if (newline == true)
		printf("\n");
	return (0);

}
