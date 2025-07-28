/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 02:16:02 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/28 02:16:34 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./memory.h"

/**
 * ft_gc_clear - Frees all the allocated
 * memory stored in the gc
 */
void	ft_gc_clear(void)
{
	ft_gc_act(NULL, CLEAR);
}

/**
 * ft_gc_remove - frees a block and removes
 * its ref from the gc
 * @addr: Address of the block to remove
 */
void	ft_gc_remove(void *addr)
{
	ft_gc_act(addr, REMOVE);
}

/**
 * ft_gc_remove_ft_split - Removes a list
 * allocated with the ft_split function
 * @list: Address of the list
 */
void	ft_gc_remove_ft_split(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		ft_gc_remove(list[i]);
		i++;
	}
	ft_gc_remove(list);
}
