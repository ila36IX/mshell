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

int	get_pipe_in(void)
{
	return (pipe_in_act(GET, 0));
}

int	get_pipe_out(void)
{
	return (pipe_out_act(GET, 0));
}

int	get_pipe_count(void)
{
	return (pipe_count_act(GET, 0));
}

int	get_current_pipe(void)
{
	return (current_pipe_act(GET, 0));
}
