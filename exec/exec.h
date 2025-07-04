#ifndef EXEC_H
# define EXEC_H

# include "../includes.h"
# include "../types.h"

typedef struct s_fd
{
	int	stdin;
	int	stdout;
	int	pipefd[2];
	int	pipe_out;
}	t_fd;

void	exec_main(t_ast *ast, char **envp);
int		setup_redirect(t_ast *ast);
void	cleanup_redirection(t_redirect *redir, int saved_stream);
int	exec_precompiled(t_ast *ast);
int	restore_fds(t_fd *fds, int pipe_in);
int	setup_fds(t_ast *ast, t_fd *fds, int pipe_in);
#endif
