/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:09:49 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:09:49 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./environ.h"
#include "../../main.h"
#include "../../libft/libft.h"

t_dict	**get_static_env_head(void)
{
	static t_dict	*s_environ_head;

	return (&s_environ_head);
}

const char	*environ_get(const char *key)
{
	t_dict	*walk;

	walk = *get_static_env_head();
	while (walk)
	{
		if (ft_strcmp(walk->key, key) == 0)
			return (walk->value);
		walk = walk->next;
	}
	return (NULL);
}

int	environ_unset(const char *key)
{
	t_dict	**cur;
	t_dict	*tmp;

	cur = get_static_env_head();
	while (*cur)
	{
		if (ft_strcmp((*cur)->key, key) == 0)
		{
			tmp = *cur;
			*cur = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return (EXIT_SUCCESS);
		}
		cur = &(*cur)->next;
	}
	return (EXIT_SUCCESS);
}

void	environ_set(const char *key, const char *value)
{
	t_dict	*node;
	t_dict	*walk;

	environ_unset(key);
	node = malloc(sizeof(t_dict));
	node->key = xgc_strdup(key);
	if (value)
		node->value = xgc_strdup(value);
	else
		node->value = NULL;
	node->next = NULL;
	if (!*get_static_env_head())
	{
		*get_static_env_head() = node;
		return ;
	}
	walk = *get_static_env_head();
	while (walk->next)
		walk = walk->next;
	walk->next = node;
}

void	environ_free(void)
{
	t_dict	*walk;
	t_dict	*tmp;

	walk = *get_static_env_head();
	while (walk)
	{
		tmp = walk->next;
		free(walk->key);
		free(walk->value);
		free(walk);
		walk = tmp;
	}
	*get_static_env_head() = NULL;
}
