/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 02:14:47 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/28 02:16:39 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

static void	debug(t_list *gc)
{
	printf("-------------\n");
	while (gc)
	{
		printf("[%p]\n", gc->content);
		gc = gc->next;
	}
	printf("-------------\n");
}

void	ft_gc_act(void *addr, t_act action)
{
	static t_list	*gc;
	t_list			*gc_node;

	if (action == CLEAR)
	{
		ft_lstclear(&gc, free);
		gc = NULL;
	}
	else if (action == INSERT)
	{
		if (ft_lstismember(gc, addr) == true)
			return ;
		gc_node = ft_lstnew(addr);
		ft_lstadd_back(&gc, gc_node);
	}
	else if (action == REMOVE)
		ft_lstremove(&gc, addr, free);
	else if (action == PRINT)
		debug(gc);
}

void	ft_gcprint(void)
{
	ft_gc_act(NULL, PRINT);
}

void	ft_gcadd_back(void *addr)
{
	if (addr)
		ft_gc_act(addr, INSERT);
}

void	*ft_malloc(size_t	size, size_t unit)
{
	void	*addr;

	addr = ft_calloc(size, unit);
	ft_gcadd_back(addr);
	return (addr);
}
