/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:14:37 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:14:41 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"
#include "../libft/libft.h"

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

bool	is_pipe(t_ast *ast)
{
	if (!ast)
		return (false);
	if (ast->type == AST_CONNECTOR)
		if (ast->connector == CONNECTOR_PIPE)
			return (true);
	return (false);
}

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

