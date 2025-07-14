#include "../../libft/libft.h"
#include "environ.h"

static int	export_print(void)
{
	t_dict	*walk;
	t_dict	*head;

	head = environ_get_head();
	if (!head)
	{
		printf("(nil)\n");
		return (EXIT_SUCCESS);
	}
	walk = head;
	while (walk)
	{
		if (walk->value)
			printf("declare -x %s=\"%s\"\n", walk->key, walk->value);
		else if (walk->key)
			printf("declare -x %s\n", walk->key);
		walk = walk->next;
	}
	return (EXIT_SUCCESS);
}

static bool	is_valid_token(const char *token)
{
	if (token == NULL)
		return (true);
	if (!ft_isalpha(token[0]) && token[0] !=  '-')
		return (false);
	if (ft_strchr(token, ' '))
		return (false);
	return (true);
}

static int	try_insert(const char *expr)
{
	char	**list;

	if (expr == NULL || ft_strlen(expr) == 0)
		return (ERR_NULL);
	list = ft_split(expr, '=');
	if (list == NULL)
		return (ERR_NULL);
	if (is_valid_token(list[0]) == false)
	{
		ft_gc_remove_ft_split(list);
		return (EXIT_FAILURE);
	}
	environ_set(list[0], list[1]);
		return (EXIT_SUCCESS);
}


int	ft_export(int ac, char **av)
{
	int	i;

	if (av == NULL)
		return (ERR_NULL);
	if (ac == 1)
		return (export_print());
	else
	{
		i = 1;
		while (av[i])
		{
			if (try_insert(av[i]) == EXIT_FAILURE)
			{
				dprintf(STDERR_FILENO,
				"minishell: export: '%s': not a valid identifier\n", av[i]);
			}
			i++;
		}
	}

	return (EXIT_SUCCESS);
}
