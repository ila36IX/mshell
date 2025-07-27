/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:10:55 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:10:55 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../parser/parser.h"
# include "./status.h"
# include "./gsetters.h"

# define MAX_PIPES_COUNT 255
# define PIPE_SIZE 2
# define GET 0
# define SET 1
# define CLEAR 2

/* Utils */
bool	is_builtin(t_ast *ast);
bool	is_pipe_next(t_ast *ast);
int		setup_redirections(t_ast *ast);
bool	is_pipe(t_ast *ast);
int		init_gates(t_ast *ast);
int		setup_fds(t_ast *ast, int pipe_in, int pipe_out);
char	*get_full_name(char *name);
bool	is_logical_connector(t_ast *ast);
int	count_nodes(t_ast *ast);

/* Gates (Pipelines + redirections) */
int		setup_gates(t_ast *ast, int node_count);
int		restore_gates(void);
int		close_gates(void);

/* Pids and processes management */
int		pid_wait_all(void);
int		pid_push(pid_t pid);
int		pid_wait_last(void);
void	pid_init(void);

/* Executer functions */
int		exec_builtin(t_ast *ast);
int		exec_simple_command(t_ast *ast);
int		exec_executable(t_ast *ast);
int		exec(t_ast *ast);
t_ast	*exec_connector(t_ast *ast, int *node_count);

/* Pipes Getters/setters */
int		pipe_init(void);

/* Static declarations settings */
int		pipe_in_act(int action, int hold);
int		pipe_out_act(int action, int hold);
int		current_pipe_act(int action, int hold);
int		pipe_count_act(int action, int hold);
int		**pipes_act(int action);

/* New implementation of the pipes */
int	**init_pipes(int *number_of_nodes, t_ast *ast);
int	setup_pipes(int count, int **pipes, int number_of_nodes);
int	close_all_pipes(int **pipes, int count);
#endif /* EXEC_H */
