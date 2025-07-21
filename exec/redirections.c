# include "./exec.h"
# include "../libft/libft.h"


# define ERR_OPEN -1
# define ERR_FILE_NOT_FOUND -2
# define ERR_NULL 1
# define PIPE_SIZE 2

static int	setup_redir_in(t_redirect *redir)
{
	int	target;

	if (!redir)
		return (FAIL);
	target = open(redir->target, O_RDONLY);
	if (target == ERR_OPEN)
		return (printf("minishell: %s: No such file or directory\n", redir->target), FAIL);
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
		return (FAIL);
	if (dup2(target, STDOUT_FILENO) == ERR_OPEN)
		return (FAIL);
	close(target);
	return (SUCCESS);
}

static int	setup_redir_heredoc(t_redirect *redir)
{
	int		fd;
	char	*filename;
	int		file_count;

	if (!redir)
		return (FAIL);
	if (redir->target == NULL)
		return (ERR_NULL);
	file_count = 42;
	filename = ft_itoa(file_count);
	if (filename == NULL)
		return (FAIL);
	while ( (access(filename, F_OK) == 0) )
	{
		file_count += 1;
		filename = ft_itoa(file_count);
	}
	fd = open(filename, O_WRONLY | O_CREAT , 0644);
	if (fd == FAIL)
		return (FAIL);
	if (write(fd, redir->target, ft_strlen(redir->target)) == ERR_OPEN)
		return (FAIL);
	fd = open(filename, O_RDONLY, 0644);
	if (dup2(fd, STDIN_FILENO) == ERR_OPEN)
		return (FAIL);
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
	i  = 0;
	redir = ast->redir;
	if (!redir)
		return (FAIL);
	while (i < ast->redir_size)
	{
		if (redir[i].type == REDIR_TYPE_IN)
			if (setup_redir_in(redir + i) == FAIL)
				return (FAIL);
		if (redir[i].type == REDIR_TYPE_OUT || redir[i].type == REDIR_TYPE_APPEND)
			if (setup_redir_out(redir + i) == FAIL)
				return (FAIL);
		if (redir[i].type == REDIR_TYPE_HEREDOC)
			if (setup_redir_heredoc(redir + i) == FAIL)
				return (FAIL);
		i++;
	}
	return (SUCCESS);
}
