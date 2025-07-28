/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:14:18 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/28 01:44:44 by sboukiou         ###   ########.fr       */
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
		return (close(target), FAIL);
	}
	if (dup2(target, STDIN_FILENO) == ERR_OPEN)
		return (close(target), FAIL);
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
		return (close(target), FAIL);
	close(target);
	return (SUCCESS);
}

static int	setup_redir_heredoc(t_redirect *redir)
{
	int		fd;
	char	*filename;
	int		file_count;

	if (!redir || redir->target == NULL)
		return (ERR_NULL);
	file_count = 42;
	filename = ft_itoa(file_count);
	if (filename == NULL)
		return (FAIL);
	while ((access(filename, F_OK) == 0))
	{
		file_count += 1;
		filename = ft_itoa(file_count);
	}
	fd = open(filename, O_WRONLY | O_CREAT, 0644);
	if (fd == FAIL)
		return (FAIL);
	write(fd, redir->target, ft_strlen(redir->target));
	fd = open(filename, O_RDONLY, 0644);
	if (dup2(fd, STDIN_FILENO) == ERR_OPEN)
		return (close(fd), FAIL);
	close(fd);
	unlink(filename);
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
	if (!redir || ast->redir_size == 0)
		return (SUCCESS);
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
