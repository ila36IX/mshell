# include "./builtins.h"

static void	env_init(t_list **head, char **env)
{
	int	i;
	t_env_dict	*dict;
	t_list	*node;
	char	**list;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		dict = ft_malloc(1, sizeof(t_env_dict));
		list = ft_split(env[i], '=');
		dict->key = list[0];
		dict->val= list[1];
		node = ft_lstnew(dict);
		ft_gcadd_back(node);
		ft_lstadd_back(head, node);
		/*ft_g_cremove(list);*/
		i++;
	}
}

static void	env_insert(t_list **head, char *key, char *value)
{
	t_env_dict	*new_dict;
	t_list		*node;

	new_dict = ft_malloc(1, sizeof(t_env_dict));
	new_dict->key = key;
	new_dict->val = value;
	node = ft_lstnew(&new_dict);
	if (!node)
		ft_gc_clear();
	ft_gcadd_back(node);
	ft_lstadd_back(head, node);
}

static void	env_remove(t_list *head, char *key)
{
	t_list	*temp;
	t_env_dict	*dict;

	temp = head;
	while (head)
	{
		temp = head;
		dict = (t_env_dict *)temp->content;
		if (ft_strcmp(dict->key, key) == 0)
			/*ft_lstdelone(temp, ft_gc_remove);*/
		head = head->next;
	}
}

int	env(char **envp)
{
	t_env_dict	*dict;
	t_list	*env;

	env = NULL;
	env_init(&env, envp);
	if (!env)
		return (EXIT_FAILURE);
	while (env)
	{
		dict = (t_env_dict *)env->content;
		if (!dict)
			return (EXIT_FAILURE);
		printf("%s=%s\n", dict->key, dict->val);
		env = env->next;
	}
	return (EXIT_SUCCESS);
}

