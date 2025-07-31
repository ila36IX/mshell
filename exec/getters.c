/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:13:50 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:13:51 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

/**
 * get_pipe_in - Gets the value of the
 * static pipe_in fd
 */
int	get_pipe_in(void)
{
	return (pipe_in_act(GET, 0));
}

/**
 * get_pipe_out - Gets the value of the
 * static pipe_out fd
 */
int	get_pipe_out(void)
{
	return (pipe_out_act(GET, 0));
}
