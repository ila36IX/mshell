/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_connector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:13:35 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/28 01:40:14 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

/**
 * move_next_pipeline - Moves a ast node
 * to the next pipeline start node
 * @ast: Ast node containing the current pipeline
 * node.
 * Return: The head of the next pipline
 * or NULL if none found
 */
t_ast	*move_next_pipeline(t_ast *ast)
{
	if (ast == NULL)
		return (NULL);
	ast = ast->next;
	while (ast && is_logical_connector(ast) == false)
		ast = ast->next;
	return (ast);
}

/**
 * exec_connector - Handles a connector
 * to decicde wether to execute the next
 * command or skip the whole pipeline
 * towards the next operator.
 * @ast: The connector node
 * @return: Head of the next executable
 * pipeline
 */
t_ast	*exec_connector(t_ast *ast)
{
	t_connector	connector;

	if (ast == NULL)
		return (NULL);
	dup2(get_pipe_in(), STDIN_FILENO);
	dup2(get_pipe_out(), STDOUT_FILENO);
	connector = ast->connector;
	if (connector == CONNECTOR_AND)
	{
		if (status_get() == SUCCESS)
			return (ast->next);
		else
			ast = move_next_pipeline(ast);
		return (ast);
	}
	if (connector == CONNECTOR_OR)
	{
		if (status_get() != SUCCESS)
			return (ast->next);
		else
			return (move_next_pipeline(ast));
	}
	else if (connector == CONNECTOR_PIPE)
		return (ast);
	return (NULL);
}
