/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:14:18 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/26 22:12:18 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include "../libft/libft.h"

#define ERR_OPEN -1
#define ERR_FILE_NOT_FOUND -2
#define ERR_NULL 1
#define PIPE_SIZE 2

static int	setup_redir_in(t_redirect *redir)
{
	int	target;

	if (!redir)
		return (FAIL);
	target = open(redir->target, O_RDONLY);
	if (target == ERR_OPEN)
	{
		status_set(ERR_NULL);
		dprintf(STDERR_FILENO,
			"minishell: %s: No such file or directory\n", redir->target);
		target = open("/dev/null", O_RDONLY);
		dup2(target, STDIN_FILENO);
		return (FAIL);
	}
	if (dup2(target, STDIN_FILENO) == ERR_OPEN)
		return (FAIL);
	close(target);
	return (SUCCESS);
}

static int	setup_redir_out(t_redirect *redir)
{
	int	target;

	if (!redir)
		return (FAIL);
	if (redir->type == REDIR_TYPE_OUT)
		target = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		target = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (target == ERR_OPEN)
		return (dprintf(STDERR_FILENO,
				"mshell: %s: %s\n", strerror(errno), redir->target), FAIL);
	if (dup2(target, STDOUT_FILENO) == ERR_OPEN)
		return (FAIL);
	close(target);
	return (SUCCESS);
}

static int	setup_redir_heredoc(t_redirect *redir)
{
	int	pipefd[PIPE_SIZE];

	if (!redir)
		return (FAIL);
	if (redir->target == NULL)
		return (ERR_NULL);
	if (pipe(pipefd) == ERR_OPEN)
		return (FAIL);
	if (write(pipefd[1], redir->target, ft_strlen(redir->target)) == ERR_OPEN)
		return (FAIL);
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == ERR_OPEN)
		return (FAIL);
	close(pipefd[0]);
	return (SUCCESS);
}

int	setup_redirections(t_ast *ast)
{
	size_t		i;
	t_redirect	*redir;

	if (!ast)
		return (FAIL);
	i = 0;
	redir = ast->redir;
	if (!redir)
		return (FAIL);
	while (i < ast->redir_size)
	{
		if (redir[i].type == REDIR_TYPE_IN)
			if (setup_redir_in(redir + i) == FAIL)
				return (FAIL);
		if (redir[i].type == REDIR_TYPE_OUT
			|| redir[i].type == REDIR_TYPE_APPEND)
			if (setup_redir_out(redir + i) == FAIL)
				return (FAIL);
		if (redir[i].type == REDIR_TYPE_HEREDOC)
			if (setup_redir_heredoc(redir + i) == FAIL)
				return (FAIL);
		i++;
	}
	return (SUCCESS);
}
