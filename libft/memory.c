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

/**
 * debug - Debugging printer for the gc
 * @gc: Head of the cache list
 */
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

/**
 * ft_gc_act - Takes an action
 * on the gc list
 * @addr: new node to insert or removed
 * @action: Action to take
 */
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

/**
 * ft_gcprint - Prints the list of gc
 */
void	ft_gcprint(void)
{
	ft_gc_act(NULL, PRINT);
}

/**
 * ft_gcadd_back - inserts a new address
 * allocated into the linked list
 * @addr: The address to add
 */
void	ft_gcadd_back(void *addr)
{
	if (addr)
		ft_gc_act(addr, INSERT);
}

/**
 * ft_malloc - A costum malloc
 * allocates and adds the address allocated
 * to the gc-cache to free it later
 */
void	*ft_malloc(size_t	size, size_t unit)
{
	void	*addr;

	addr = ft_calloc(size, unit);
	ft_gcadd_back(addr);
	return (addr);
}
