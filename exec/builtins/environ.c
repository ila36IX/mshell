#include "./environ.h"
#include "../../main.h"
# include "../../libft/libft.h"

# define ENV_SIZE 100
t_dict	*g_environ_head = NULL;

const char	*environ_get(const char *key)
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

int	environ_unset(const char *key)
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

int	environ_print(void)
{
	t_dict	*walk;

	if (!g_environ_head)
	{
		printf("(nil)\n");
		return (EXIT_SUCCESS);
	}
	walk = g_environ_head;
	while (walk)
	{
		printf("[%s] = %s\n", walk->key, walk->value);
		walk = walk->next;
	}
	return (EXIT_SUCCESS);
}

void	environ_init(const char **envp)
{
	int	i;
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
	char **list;
	int	i;
	t_dict	*temp;
	char	*str_temp;

	temp = g_environ_head;
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
		temp =  temp->next;
		i++;
	}
	return (list);
}
