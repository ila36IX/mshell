#include "../../main.h"

t_env_dict	*get_dict(char *expression)
{
	int			i;
	t_env_dict	*new_dict;
	char		**list;

	if (!expression)
		return (NULL);
	i = 1;
	if (ft_strchr(expression, '=') == NULL)
		return (NULL);
	new_dict = (t_env_dict *)ft_malloc(sizeof(t_env_dict), 1);
	if (!new_dict)
		return (NULL);
	list = ft_split(expression, '=');
	if (!list)
		return (NULL);
	if (ft_isalpha(list[0][0]) == 0)
		return (NULL);
	new_dict->key  = list[0];
	new_dict->val = list[1];
	/*ft_gcremove_split(list);*/
	return (new_dict);
}

/*
 * env_insert - Inserts a new dict(key,val) into the env-list
 * @head: Head of the linked list
 * @key: Key, Ex: PWD
 * @value: value, Ex: /home/sboukiou
 */
void	bin_export(t_simple_cmd cmd, t_list *env)
{
	t_env_dict	*new_dict;
	t_list		*node;
	int			i;

	i = 0;
	while (cmd.argv[i])
	{
		new_dict = get_dict(cmd.argv[i]);
		node = ft_lstnew(&new_dict);
		if (!node)
			ft_gc_clear();
		ft_gcadd_back(node);
		ft_lstadd_back(&env, node);
		printf("[Added new node to env]\n");
		i++;
	}
}
