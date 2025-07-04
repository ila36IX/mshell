# include "../includes.h"
# include "./exec.h"

int	setup_fds(t_ast *ast, t_fd *fds, int pipe_in)
{
	int	redirect;

	fds->stdin = dup(STDIN_FILENO);
	fds->stdout = dup(STDOUT_FILENO);
	fds->pipe_out = -1;
	if (ast->next && ast->next->type == AST_CONNECTOR
			&& ast->next->connector == CONNECTOR_PIPE)
	{
		pipe(fds->pipefd);
		dup2(fds->pipefd[1], STDOUT_FILENO);
		fds->pipe_out = fds->pipefd[0];
		close(fds->pipefd[1]);
	}
	if (pipe_in != FAIL)
		dup2(pipe_in, STDIN_FILENO);
	if (fds->stdin == FAIL || fds->stdout == FAIL)
		return (FAIL);
	redirect = setup_redirect(ast);
	if (redirect == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	restore_fds(t_fd *fds, int pipe_in)
{
	dup2(fds->stdin, STDIN_FILENO);
	dup2(fds->stdout, STDOUT_FILENO);
	close(fds->stdin);
	close(fds->stdout);
	close(pipe_in);
	return (SUCCESS);
}
