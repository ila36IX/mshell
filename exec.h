#ifndef EXEC_H
# define EXEC_H

# include "./main.h"

int exec_main(t_ast *ast, char **envp);

int	setup_redirections(t_ast *ast, int *target);
void	cleanup_redirection(t_redirect *redir, int saved_stream);
#endif
