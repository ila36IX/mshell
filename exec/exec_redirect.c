# include "./exec.h"
# include "../libft/libft.h"

int	single_redirections(t_redirect *redir, int *target_fd)
{
	int	saved_stream;
	char	*herdoc_line;

	if (!redir)
		return (-1);

	saved_stream = -2;
	if (redir->type == REDIR_TYPE_OUT)
	{
		saved_stream = dup(STDOUT_FILENO);
		*target_fd = open(redir->target, O_WRONLY | O_CREAT, 0644);
		if (*target_fd == -1)
			perror("Open");
		if (dup2(*target_fd, STDOUT_FILENO) ==  -1)
			perror("dup2");
	}
	else if (redir->type == REDIR_TYPE_APPEND)
	{
		saved_stream = dup(STDOUT_FILENO);
		*target_fd = open(redir->target, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (*target_fd == -1)
			perror("open");
		if (dup2(*target_fd, STDOUT_FILENO) ==  -1)
			perror("dup2");
	}
	else if (redir->type == REDIR_TYPE_IN)
	{
		saved_stream = dup(STDIN_FILENO);
		*target_fd = open(redir->target, O_RDONLY | O_CREAT, 0644);
		if (*target_fd == -1)
			perror("open");
		if (dup2(*target_fd, STDIN_FILENO) ==  -1)
			perror("dup2");
	}
	else if (redir->type == REDIR_TYPE_HEREDOC)
	{
		saved_stream = dup(STDIN_FILENO);
		while (true)
		{
			herdoc_line = readline("> ");
			if (!herdoc_line || ft_strcmp(herdoc_line, redir->target) == 0) {
				free(herdoc_line);
				break;
			}
		}
	}
	return (saved_stream);
}

void	cleanup_redirection(t_redirect *redir, int saved_stream)
{
	if (redir->type == REDIR_TYPE_IN)
		dup2(saved_stream, STDIN_FILENO);
	else if (redir->type == REDIR_TYPE_OUT || redir->type == REDIR_TYPE_APPEND)
		dup2(saved_stream, STDOUT_FILENO);
	if (saved_stream < 0)
		close(saved_stream);
}

int	setup_redirections(t_ast *ast, int *target)
{
	int	saved_stream;
	t_redirect	*redir;
	size_t	i;

	i = 0;
	redir = ast->redir;
	while (i < ast->redir_size)
	{
		saved_stream = single_redirections(redir + i, target);
		if (i + 1 < ast->redir_size && redir[i + 1].type != REDIR_TYPE_HEREDOC)
		{
			cleanup_redirection(redir + i, saved_stream);
			if (*target != -1)
				close(*target);
		}
		i++;
	}
	return (saved_stream);
}

