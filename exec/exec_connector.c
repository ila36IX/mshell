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

t_ast	*exec_connector(t_ast *ast)
{
	t_connector	connector;

	if (ast == NULL)
		return (NULL);
	connector = ast->connector;
	if (connector == CONNECTOR_AND)
	{
		if (status_get() == SUCCESS)
			return (ast->next);
		else
		{
			ast = ast->next;
			while (ast && is_logical_connector(ast) == false)
				ast = ast->next;
			return (ast);
		}
	}
	if (connector == CONNECTOR_OR)
	{
		if (status_get() != SUCCESS)
			return (ast->next);
		else
		{
			ast = ast->next;
			while (ast && is_logical_connector(ast) == false)
				ast = ast->next;
			return (ast);
		}
	}
	else if (connector == CONNECTOR_PIPE)
		return (ast);
	return (NULL);
}
