/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:11:24 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:13:23 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include "../includes.h"
#include "../libft/libft.h"
#include "./builtins/builtins.h"

static int	call_builtins(t_ast *ast)
{
	char	**av;
	int		ac;
	int		status;

	av = ast->simple_cmd.argv;
	ac = ast->simple_cmd.argc;
	if (ac == 0)
		return (status_set(SUCCESS), SUCCESS);
	status = 0;
	if (ft_strcmp(av[0], "echo") == SUCCESS)
		status = ft_echo(ac, av);
	if (ft_strcmp(av[0], "cd") == SUCCESS)
		status = ft_cd(ac, av);
	if (ft_strcmp(av[0], "pwd") == SUCCESS)
		status = ft_pwd(ac, av);
	if (ft_strcmp(av[0], "export") == SUCCESS)
		status = ft_export(ac, av);
	if (ft_strcmp(av[0], "unset") == SUCCESS)
		status = ft_unset(ac, av);
	if (ft_strcmp(av[0], "env") == SUCCESS)
		status = ft_env(ac, av);
	if (ft_strcmp(av[0], "exit") == SUCCESS)
		status = ft_exit(ac, av);
	return (status_set(status), status);
}

int	exec_builtin(t_ast *ast)
{
	int		status;

	if (ast == NULL)
		return (ERR_NULL);
	if (ast->simple_cmd.argc == 0)
		return (SUCCESS);
	status = call_builtins(ast);
	return (status);
}
