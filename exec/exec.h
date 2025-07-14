#ifndef EXEC_H
# define EXEC_H

# include "../parser/parser.h"

# define MAX_PIPES_COUNT 255
# define PIPE_SIZE 2

/* Utils */
bool	is_builtin(t_ast *ast);
bool	is_pipe_next(t_ast *ast);
int	setup_redirections(t_ast *ast);
bool	is_pipe(t_ast *ast);


/* Executer functions */
int	exec_builtin(t_ast *ast);
int	exec_simple_command(t_ast *ast);
int exec_executable(t_ast *ast);
int	exec(t_ast *ast);


/* Pipes Getters/setters */
int	pipe_init(void);
int	pipe_get_in(void);
int	pipe_get_out(void);
int	pipe_setall(t_ast *ast, int pipes[MAX_PIPES_COUNT][PIPE_SIZE]);

#endif /* EXEC_H */
