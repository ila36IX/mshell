#ifndef EXEC_H
# define EXEC_H

# include "./main.h"

int exec_main(t_ast *ast, char **envp);

int	setup_redirect(t_ast *ast);
void	cleanup_redirection(t_redirect *redir, int saved_stream);
#endif
