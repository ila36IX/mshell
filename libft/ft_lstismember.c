#include "./libft.h"

bool	ft_lstismember(t_list *head, void *data)
{
	t_list	*temp;


	if (!head || !data)
		return (false);
	temp = head;
	while (temp)
	{
		if (temp->content == data)
			return (true);
		temp = temp->next;
	}
	return (false);
}
