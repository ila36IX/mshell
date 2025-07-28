/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 02:15:01 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/28 02:16:18 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "../types.h"

/**
 * s_act - Enumeration for and action
 * taken by G-collector module
 */
typedef enum s_act
{
	CLEAR,
	INSERT,
	REMOVE,
	PRINT,
}	t_act;

void	ft_gc_act(void *addr, t_act action);

void	*ft_malloc(size_t	size, size_t unit);
void	ft_gcadd_back(void *addr);
void	ft_gc_clear(void);
void	ft_gc_remove_ft_split(char **list);
void	ft_gc_remove(void *addr);
/* For debuggin purposes */
void	ft_gcprint(void);
#endif /* MEMORY_H */
