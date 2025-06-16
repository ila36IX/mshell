#include "../../main.h"
#include "environ.h"

void	insert_new_node(char *expression)
{
	char		**list;

	if (!expression)
		return ;
	if (ft_strchr(expression, '=') == NULL)
		return ;
	list = ft_split(expression, '=');
	if (!list)
		return ;
	if (ft_isalpha(list[0][0]) == 0)
		return ;
	environ_set(list[0], list[1]);
	/*ft_gcremove_split(list);*/
}

/*
 * env_insert - Inserts a new dict(key,val) into the env-list
 * @head: Head of the linked list
 * @key: Key, Ex: PWD
 * @value: value, Ex: /home/sboukiou
 */
void	bin_export(t_simple_cmd cmd)
{
	int			i;

	i = 0;
	while (cmd.argv[i])
	{
		insert_new_node(cmd.argv[i]);
		printf("[Added new node to env]\n");
		i++;
	}
}
