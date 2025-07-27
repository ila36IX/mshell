/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_connector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:13:35 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:13:35 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

static void	reset(int *node_count)
{
	pid_wait_all();
	*node_count = 0;
}

t_ast	*exec_connector(t_ast *ast, int *node_count)
{
	t_connector	connector;

	if (ast == NULL)
		return (NULL);
	connector = ast->connector;
	if (connector == CONNECTOR_AND)
	{
		reset(node_count);
		if (status_get() == SUCCESS)
			return (ast);
		else
			return (ast->next);
	}
	if (connector == CONNECTOR_OR)
	{
		reset(node_count);
		if (status_get() != SUCCESS)
			return (ast);
		else
			return (ast->next);
	}
	else if (connector == CONNECTOR_PIPE)
		return (ast);
	return (NULL);
}
