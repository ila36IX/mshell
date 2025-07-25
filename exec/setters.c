/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:14:21 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:14:22 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

int	set_pipe_in(int value)
{
	return (pipe_in_act(SET, value));
}

int	set_pipe_out(int value)
{
	return (pipe_in_act(SET, value));
}

int	set_pipe_count(int value)
{
	return (pipe_count_act(SET, value));
}

int	set_current_pipe(int value)
{
	return (current_pipe_act(SET, value));
}
