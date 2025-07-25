/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:09:39 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:09:45 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes.h"
#include "./environ.h"
#include "../status.h"

int	ft_env(int ac, char **av)
{
	if (av == NULL)
		return (status_set(ERR_NULL), ERR_NULL);
	if (ac != 1)
	{
		dprintf(STDERR_FILENO,
			"minishell: env: No arguments shall be provided\n");
		return (status_set(EXIT_FAILURE), EXIT_FAILURE);
	}
	if (environ_print() != EXIT_SUCCESS)
		return (status_set(EXIT_FAILURE), EXIT_FAILURE);
	status_set(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
