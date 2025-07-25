/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:10:48 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:10:49 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes.h"
#include "./environ.h"

int	ft_unset(int ac, char **av)
{
	int	i;

	if (ac == 1)
		return (EXIT_SUCCESS);
	if (av == NULL)
		return (ERR_NULL);
	i = 0;
	while (av[i])
	{
		environ_unset(av[i]);
		i++;
	}
	return (0);
}
