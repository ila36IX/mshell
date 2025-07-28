/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstismember.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 02:13:37 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/28 02:13:40 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
