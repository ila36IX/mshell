/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsetters.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:11:03 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:11:04 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GSETTERS_H
# define GSETTERS_H

/* Getters */
#include <fcntl.h>
int	get_pipe_in(void);
int	get_pipe_out(void);
int	get_pipe_count(void);
int	get_current_pipe(void);

/* Setters */
int	set_pipe_in(int value);
int	set_pipe_out(int value);
int	set_pipe_count(int value);
int	set_current_pipe(int value);
pid_t	pid_get(void);

#endif /* GSETTERS_H */
