/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:09:59 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:15:07 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./environ.h"
#include "../../libft/libft.h"

int	environ_print(void)
{
	t_dict	*walk;

	if (!*get_static_env_head())
	{
		printf("(nil)\n");
		return (EXIT_SUCCESS);
	}
	walk = *get_static_env_head();
	while (walk)
	{
		if (walk->key && walk->value)
			printf("%s=%s\n", walk->key, walk->value);
		walk = walk->next;
	}
	return (EXIT_SUCCESS);
}

void	environ_init(const char **envp)
{
	int		i;
	char	**list;

	i = 0;
	while (envp[i])
	{
		list = ft_split(envp[i], '=');
		if (!list)
			return ;
		environ_set(list[0], list[1]);
		ft_gc_remove_ft_split(list);
		i++;
	}
}

char	**environ_array_execve(void)
{
	char	**list;
	int		i;
	t_dict	*temp;
	char	*str_temp;

	temp = *get_static_env_head();
	list = ft_malloc(ENV_SIZE, sizeof(char *));
	if (!list)
		return (NULL);
	i = 0;
	while (temp)
	{
		str_temp = ft_strjoin(temp->key, "=");
		if (!str_temp)
			return (NULL);
		list[i] = ft_strjoin(str_temp, temp->value);
		if (!list[i])
			return (NULL);
		ft_gc_remove(str_temp);
		temp = temp->next;
		i++;
	}
	return (list);
}

t_dict	*environ_get_head(void)
{
	return (*get_static_env_head());
}
