#include "environ.h"

t_dict	*g_environ_head = NULL;

char	*envron_get(const char *key)
{
	t_dict	*walk;

	walk = g_environ_head;
	while (walk)
	{
		if (ft_strcmp(walk->key, key) == 0)
			return (walk->value);
		walk = walk->next;
	}
	return (NULL);
}

void	environ_unset(const char *key)
{
	t_dict	**cur;
	t_dict	*tmp;

	cur = &g_environ_head;
	while (*cur)
	{
		if (ft_strcmp((*cur)->key, key) == 0)
		{
			tmp = *cur;
			*cur = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		cur = &(*cur)->next;
	}
}

void	environ_set(const char *key, const char *value)
{
	t_dict	*node;
	t_dict	*walk;

	environ_unset(key);
	node = malloc(sizeof(t_dict));
	node->key = xgc_strdup(key);
	node->value = xgc_strdup(value);
	node->next = NULL;
	if (!g_environ_head)
	{
		g_environ_head = node;
		return ;
	}
	walk = g_environ_head;
	while (walk->next)
		walk = walk->next;
	walk->next = node;
}

void	environ_free(void)
{
	t_dict	*walk;
	t_dict	*tmp;

	walk = g_environ_head;
	while (walk)
	{
		tmp = walk->next;
		free(walk->key);
		free(walk->value);
		free(walk);
		walk = tmp;
	}
	g_environ_head = NULL;
}

void	environ_print(void)
{
	t_dict	*walk;

	if (!g_environ_head)
	{
		printf("(nil)\n");
		return ;
	}
	walk = g_environ_head;
	while (walk)
	{
		printf("[%s] = %s\n", walk->key, walk->value);
		walk = walk->next;
	}
}
