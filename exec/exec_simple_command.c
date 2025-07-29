/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple_command.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:13:44 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/28 01:41:34 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include "../libft/libft.h"
#include "../signals/signal_handler.h"

bool	is_valid_executable(t_ast *ast)
{
	char	**av;
	int		ac;
	int		status;
	char	*cmd_name;

	if (ast == NULL)
		return (ERR_NULL);
	if (ast->simple_cmd.argc == 0)
		return (SUCCESS);
	av = ast->simple_cmd.argv;
	ac = ast->simple_cmd.argc;
	status = 0;
	cmd_name = get_full_name(av[0]);
	if (cmd_name == NULL)
		return (false);
	return (true);
}

static int	set_status_with_signals(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			status_set(EXIT_STATUS_SIGINT);
		else if (WTERMSIG(status) == SIGQUIT)
			status_set(EXIT_STATUS_SIGQUIT);
		else
			status_set(WEXITSTATUS(status));
	}
	else
		status_set(WEXITSTATUS(status));
	return (SUCCESS);
}

int	exec_simple_command(t_ast *ast)
{
	int		status;
	pid_t	pid;

	printf("Called a simple_command setup\n");
	if (ast == NULL || ast->simple_cmd.argc == 0)
		return (status_set(SUCCESS), SUCCESS);
	if (ft_strlen(ast->simple_cmd.argv[0]) == 0)
		return (status_set(SUCCESS), SUCCESS);
	status = 0;
	if (is_builtin(ast) == true)
		exec_builtin(ast);
	else if (is_valid_executable(ast) == false)
		return (ERR_NULL);
	else
	{
		pid = fork();
		if (pid == FAIL)
			return (status_set(ERR_NULL), ERR_NULL);
		if (pid == 0)
		{
			exec_executable(ast);
			ft_clean();
			exit(status_get());
		}
		waitpid(pid, &status, 0);
		set_status_with_signals(status);
	}
	return (status_get());
}
