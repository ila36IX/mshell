/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:10:31 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:10:34 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "environ.h"
#include "../status.h"

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
			printf("[exported] %s=\"%s\"\n", walk->key, walk->value);
		else if (walk->key)
			printf("[exported] %s\n", walk->key);
		walk = walk->next;
	}
	return (EXIT_SUCCESS);
}

static bool	is_valid_token(const char *token)
{
	int	i;

	if (token == NULL)
		return (true);
	if (!ft_isalpha(token[0]) && token[0] != '_')
		return (false);
	i = 0;
	while (token[i])
	{
		if (!ft_isalpha(token[i]) && token[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static int	try_insert(const char *expr)
{
	char	*key;
	char	*value;

	if (expr == NULL || ft_strlen(expr) == 0)
		return (ERR_NULL);
	value = ft_strchr(expr, '=');
	if (value)
	{
		key = ft_substr(expr, 0, value - expr);
		value += 1;
	}
	else
		key = (char *)expr;
	if (is_valid_token(key) == false)
	{
		status_set(1);
		return (EXIT_FAILURE);
	}
	environ_set(key, value);
	return (EXIT_SUCCESS);
}

int	ft_export(int ac, char **av)
{
	int	i;

	status_set(0);
	if (av == NULL)
		return (status_set(EXIT_FAILURE), ERR_NULL);
	if (ac == 1)
		return (export_print());
	else
	{
		i = 1;
		while (av[i])
		{
			if (try_insert(av[i]) == EXIT_FAILURE)
			{
				ft_dprintf(STDERR_FILENO,
					"minishell: export: '%s': not a valid identifier\n", av[i]);
				status_set(EXIT_FAILURE);
			}
			i++;
		}
	}
	return (status_get());
}
