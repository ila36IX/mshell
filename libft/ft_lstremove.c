# include "./libft.h"
# include <stdio.h>

/**
 * ft_ltsremove - removes a node from a linked-list
 * @head: Head/ first node of the list
 * @node: node to remove
 */
void	ft_lstremove(t_list **head, void *data, void (*del)(void *))
{
	t_list	*temp;
	t_list	*next;

	if (!head || !*head || !data)
		return ;
	if (data == (*head)->content)
	{
		del(data);
		free(*head);
		*head = NULL;
		return ;
	}
	temp = *head;
	while (temp)
	{
		next = temp->next;
		if (next && next->content == data)
		{
			temp->next = next->next;
			del(data);
			free(next);
		}
		temp = temp->next;
	}
}
