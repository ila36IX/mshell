# include "./main.h"

# define ERR_OPEN -1
# define ERR_FILE_NOT_FOUND -2
# define ERR_NULL 1

static int	setup_single_redir(t_redirect *redir)
{
	int	target_fd;

	if (!redir)
		return (ERR_NULL);

	if (redir->type == REDIR_TYPE_IN)
	{
		target_fd = open(redir->target, O_RDONLY, 0644);
		if (target_fd == ERR_OPEN)
			return (ERR_OPEN);
		if (dup2(target_fd, STDIN_FILENO) == ERR_OPEN)
		{
			printf("mshell: %s: No such file or directory\n", redir->target);
			return (ERR_OPEN);
		}
		close(target_fd);
	}
	if (redir->type == REDIR_TYPE_OUT || redir->type == REDIR_TYPE_APPEND)
	{
		if (redir->type == REDIR_TYPE_OUT)
			target_fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->type == REDIR_TYPE_APPEND)
			target_fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND | O_TRUNC, 0644);
		if (target_fd == ERR_OPEN)
			return (ERR_OPEN);
		if (dup2(target_fd, STDOUT_FILENO) == ERR_OPEN)
			perror("[DUP2]");
		close(target_fd);
	}
	if (redir->type == REDIR_TYPE_HEREDOC)
	{
		char	*line;
		int	pipefd[2];
		pipe(pipefd);
		while (true)
		{
			line = readline("> ");
			if (line == NULL)
				break;
			if (ft_strcmp(line, redir->target) == 0)
			{
				free(line);
				break;
			}
			write(pipefd[1], line, ft_strlen(line));
			write(pipefd[1], "\n", 1);
		}
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	return (target_fd);
}

static void	create_targets(t_redirect *redir, size_t size)
{
	size_t	i;
	int		fd;

	i = 0;
	while (i < size)
	{
		if (redir[i].type != REDIR_TYPE_IN && redir[i].type != REDIR_TYPE_HEREDOC)
		{
			fd = open(redir->target, O_CREAT, 0644);
			if (fd == ERR_OPEN)
				perror("[OPEN]");
			close(fd);
		}
		i++;
	}
}

int	setup_redirect(t_ast *ast)
{
	t_redirect	*redir;
	size_t		i;
	int			in_file;
	int			out_file;

	if (!ast || !ast->redir)
		return (ERR_NULL);
	redir = ast->redir;
	i = 0;
	in_file = -1;
	out_file = -1;
	create_targets(redir, ast->redir_size);
	while (i < ast->redir_size)
	{
		if (redir[i].type == REDIR_TYPE_IN || redir[i].type == REDIR_TYPE_HEREDOC)
			in_file = i;
		if (redir[i].type == REDIR_TYPE_OUT || redir[i].type == REDIR_TYPE_APPEND)
			out_file = i;
		i++;
	}
	if (in_file != ERR_OPEN)
		printf("Last in file --> [%s]\n", redir[in_file].target);
	if (out_file != ERR_OPEN)
		printf("Last out file --> [%s]\n", redir[out_file].target);
	if (in_file != ERR_OPEN)
		in_file = setup_single_redir(redir + in_file);
	if (out_file != ERR_OPEN)
		out_file = setup_single_redir(redir + out_file);
	if (in_file == ERR_FILE_NOT_FOUND)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
