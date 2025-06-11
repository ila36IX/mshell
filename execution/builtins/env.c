# include "./builtins.h"

/*
 * env_init - Initialized a linked list of env-variables
 * from a key.val array
 * @head: Head of the linked list
 * @env: Array containing the env variables with the format:
 * ["key=val"]
 */

t_list	*env_init(char **env)
{
	int	i;
	t_env_dict	*dict;
	t_list	*node;
	t_list	*head;
	char	**list;

	if (!env)
		return (NULL);
	i = 0;
	head = NULL;
	while (env[i])
	{
		dict = ft_malloc(1, sizeof(t_env_dict));
		list = ft_split(env[i], '=');
		dict->key = list[0];
		dict->val= list[1];
		node = ft_lstnew(dict);
		ft_gcadd_back(node);
		ft_lstadd_back(&head, node);
		/*ft_gc_remove_split(list);*/
		i++;
	}
	return (head);
}


/**
	* env_get_value - Gets the value based on a key
	* @key: Key to check for its value
	* Return: Value or NULL if its not found
 */
char	*env_get_value(char *key, t_list *env)
{
	t_list	*temp;
	t_env_dict	*dict;

	temp = env;
	while (temp)
	{
		dict = (t_env_dict *)temp->content;
		if (ft_strcmp(dict->key, key) == 0)
			return (dict->val);
		temp = temp->next;
	}
	return (NULL);
}

/*
 * env_insert - Inserts a new dict(key,val) into the env-list
 * @head: Head of the linked list
 * @key: Key, Ex: PWD
 * @value: value, Ex: /home/sboukiou
 */
void	export(t_list **head, char *key, char *value)
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

/*
 * unset - Removes a key/val node from the env (Used by unset)
 * @head: Head of the linked list
 * @key: Key, Ex: PWD
 */
void	unset(t_list *head, char *key)
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


/*
 * env - Prints all environment variables with the format ("%s=%s", key, val)
 * to STDOUT
 * @envp: Array of strs containing the key-val for each variable
 * Return: 0 if succeeded or EXIT_FAILURE otherwise
 */

int	env(char **envp)
{
	t_env_dict	*dict;
	t_list	*env;

	env = NULL;
	env_init(envp);
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

