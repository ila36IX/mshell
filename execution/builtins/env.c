# include "./builtins.h"

void	env_init(t_list **head, char **env)
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
		/*gc_clear_node(list, ft_split_free);*/
		i++;
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

