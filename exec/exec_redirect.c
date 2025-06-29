# include "../libft/libft.h"


# define ERR_OPEN -1
# define ERR_FILE_NOT_FOUND -2
# define ERR_NULL 1
# define SUCCESS 0
# define FAIL 1

static int	setup_redir_out(t_redirect *redir)
{
	int	target;

	if (!redir)
		return (FAIL);
	target = 0;
	if (redir->type == REDIR_TYPE_OUT)
		target = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (redir->type == REDIR_TYPE_APPEND)
		target = open(redir->target, O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644);
	if (target == ERR_OPEN)
		return (FAIL);
	if (dup2(target, STDOUT_FILENO) != EXIT_SUCCESS)
		return (FAIL);
	close(target);
	return (SUCCESS);
}

static int	setup_redir_in(t_redirect *redir)
{
	int	target;

	if (!redir)
		return (FAIL);
	target = open(redir->target, O_RDONLY | O_TRUNC, 0644);
	if (target == ERR_OPEN)
		return (FAIL);
	if (dup2(target, STDIN_FILENO) != EXIT_SUCCESS)
		return (FAIL);
	close(target);
	return (SUCCESS);
}


static int	setup_redir_heredoc(t_redirect *redir)
{
	int		pipefd[2];
	char	*line;

	if (!redir)
		return (FAIL);
	if (pipe(pipefd) != SUCCESS)
		return (FAIL);
	while (true)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_strcmp(line, redir->target) == 0)
		{
			free(line);
			break;
		}
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
	}
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	return (SUCCESS);
}

static void	fake_heredoc(t_redirect *redir)
{

	char	*line;

	if (!redir)
		return ;
	while (true)
	{
		line = readline("> ");
		if (!line)
			break;
		if (ft_strcmp(line, redir->target) == 0)
		{
			free(line);
			break;
		}
	}
}

int	setup_redirect(t_ast *ast)
{
	t_redirect	*redir;
	size_t		i;
	int			last_heredoc;

	if (!ast)
		return (FAIL);
	redir = ast->redir;

	i = 0;
	while (i < ast->redir_size)
	{
		if (redir[i].type == REDIR_TYPE_HEREDOC)
			last_heredoc = i;
		i++;
	}
	i  = 0;
	while (i < ast->redir_size)
	{
		if (redir[i].type == REDIR_TYPE_OUT)
			return (setup_redir_out(redir + i));
		else if (redir[i].type == REDIR_TYPE_APPEND)
			return (setup_redir_out(redir + i));
		else if (redir[i].type == REDIR_TYPE_IN)
			return (setup_redir_in(redir + i));
		else if (redir[i].type == REDIR_TYPE_HEREDOC)
		{
			if ((int )(i) == last_heredoc)
				return (setup_redir_heredoc(redir + i));
			else
				fake_heredoc(redir + i);
		}
		i++;
	}
	return (SUCCESS);
}
