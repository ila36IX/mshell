#ifndef EXEC_H
# define EXEC_H

# include "../includes.h"
# include "../types.h"

# define PID_MAX 1024

typedef struct s_tunnel
{
	pid_t	out;
	pid_t	in;
	pid_t	pipes[2];
}	t_tunnel;

int	exec_main(t_ast *ast, char **envp);
int	exec_simple_cmd(t_ast *ast, int pipes[255][2], int pipe_count, int command_count);
int	execute_simple_command(t_ast *ast);
int		setup_redirect(t_ast *ast);
int	exec_precompiled(t_ast *ast);
int	setup_fds(t_ast *ast, int pipe_in, int pipe_out);
int	setup_pipes(t_ast *ast);
int exec_connector(t_ast *ast);
bool	pipe_next(t_ast *ast);
#endif
