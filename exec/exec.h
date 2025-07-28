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
char	*get_full_name(char *name);
bool	is_logical_connector(t_ast *ast);
int		count_nodes(t_ast *ast);

/* Pids and processes management */
int		pid_wait_all(void);
int		pid_push(pid_t pid);
void	pid_init(void);

/* Executer functions */
int		exec_builtin(t_ast *ast);
int		exec_simple_command(t_ast *ast);
int		exec_executable(t_ast *ast);
int		exec(t_ast *ast);
t_ast	*exec_connector(t_ast *ast);

/* Static declarations settings */
int		pipe_in_act(int action, int hold);
int		pipe_out_act(int action, int hold);

/* implementation of the pipes --> pipe.c */
int		**init_pipes(int *number_of_nodes, t_ast *ast);
int		setup_pipes(int count, int **pipes, int number_of_nodes);
int		close_all_pipes(int **pipes, int count);
#endif /* EXEC_H */
