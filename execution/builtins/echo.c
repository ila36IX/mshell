# include "./builtins.h"


/**
	 * expand_write - Expands and prints a env-variable
	 * @var: Env variable key
 */
void	expand_write(char *var)
{
	char	*val;

	if (!var)
		return ;

	if (var[0] == '$')
	{
		val = env_get_value(var + 1);
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

int	echo(char **av, t_redirect *redir)
{
	int	i;
	bool	newline;

	UNSET(redir);
	if (!av)
		return (EXIT_FAILURE);
	i = 1;
	while (av[i])
	{
		if (ft_strcmp(av[i], "-n") == 0)
			newline = true;
		else
			expand_write(av[i]);
		i++;
	}
	if (newline == true)
		printf("\n");
	return (0);

}
/*{*/
/*	int	written;*/
/*	int	text_len;*/
/**/
/*	if (text == NULL)*/
/*		return (EXIT_FAILURE);*/
/*	text_len = ft_strlen(text);*/
/*	if (newline == true)*/
/*		written = printf("%s\n", text);*/
/*	else*/
/*		written = printf("%s", text);*/
/*	if (text_len > written)*/
/*		return (EXIT_FAILURE);*/
/*	return (written);*/
/*}*/
