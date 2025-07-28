/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:14:24 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/28 01:45:00 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

int	pipe_in_act(int action, int hold)
{
	static int	pipe_in;

	if (action == GET)
		return (pipe_in);
	if (action == SET)
		pipe_in = hold;
	return (pipe_in);
}

int	pipe_out_act(int action, int hold)
{
	static int	pipe_out;

	if (action == GET)
		return (pipe_out);
	if (action == SET)
		pipe_out = hold;
	return (pipe_out);
}
