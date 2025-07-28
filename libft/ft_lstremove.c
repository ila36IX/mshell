/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 02:13:52 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/28 02:14:00 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

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
