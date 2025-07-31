/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:14:37 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/28 01:45:12 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"
#include "../libft/libft.h"
#include "./gsetters.h"
#include "./builtins/environ.h"

/**
 * is_builtin - Check if a command
 * is a builtin
 * @ast: Command node
 * Return: true if a builtin
 * false otherwise
 */
bool	is_builtin(t_ast *ast)
{
	char	**av;

	if (ast == NULL)
		return (false);
	av = ast->simple_cmd.argv;
	if (av == NULL)
		return (printf("NULLED av\n"), false);
	if (ft_strcmp(av[0], "echo") == SUCCESS)
		return (true);
	if (ft_strcmp(av[0], "cd") == SUCCESS)
		return (true);
	if (ft_strcmp(av[0], "pwd") == SUCCESS)
		return (true);
	if (ft_strcmp(av[0], "export") == SUCCESS)
		return (true);
	if (ft_strcmp(av[0], "unset") == SUCCESS)
		return (true);
	if (ft_strcmp(av[0], "env") == SUCCESS)
		return (true);
	if (ft_strcmp(av[0], "exit") == SUCCESS)
		return (true);
	return (false);
}

/**
 * is_pipe_next - Checks if a node
 * has a pipe next
 * @ast: node to check
 * Return: pipe next ? true : false
 */
bool	is_pipe_next(t_ast *ast)
{
	if (!ast)
		return (false);
	if (ast->next)
	{
		ast = ast->next;
		if (ast->type == AST_CONNECTOR)
			if (ast->connector == CONNECTOR_PIPE)
				return (true);
	}
	return (false);
}

/**
 * is_pipe - Checks if a node
 * is a pipe connector
 * @ast: node to check
 * Return: pipe ? true : false
 */
bool	is_pipe(t_ast *ast)
{
	if (!ast)
		return (false);
	if (ast->type == AST_CONNECTOR)
		if (ast->connector == CONNECTOR_PIPE)
			return (true);
	return (false);
}

/**
 * is_logical_connector - Checks if a node
 * is a logical connector (&& or ||)
 * @ast: node to check
 * Return: connector ? true : false
 */
bool	is_logical_connector(t_ast *ast)
{
	if (ast == NULL)
		return (true);
	if (ast->type == AST_CONNECTOR)
	{
		if (ast->connector == CONNECTOR_AND)
			return (true);
		if (ast->connector == CONNECTOR_OR)
			return (true);
	}
	return (false);
}

/**
 * count_nodes - Counts number
 * of nodes or commands in a pipeline
 * @ast: Head of the pipeline
 * Return: Number of nodes
 */
int	count_nodes(t_ast *ast)
{
	int	count;

	count = 0;
	while (is_logical_connector(ast) == false)
	{
		if (ast->type == AST_SIMPLE_COMMAND
			|| ast->type == AST_SUBSHELL)
			count += 1;
		ast = ast->next;
	}
	return (count);
}
