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

/**
 * pipe_in_act - Takes action on a static int
 * @action: GET or SET
 * @hold: Value to set in case of SET action
 * @return: The value of the integer
 */
int	pipe_in_act(int action, int hold)
{
	static int	pipe_in;

	if (action == GET)
		return (pipe_in);
	if (action == SET)
		pipe_in = hold;
	return (pipe_in);
}

/**
 * pipe_in_out - Takes action on a static int
 * @action: GET or SET
 * @hold: Value to set in case of SET action
 * @return: The value of the integer
 */
int	pipe_out_act(int action, int hold)
{
	static int	pipe_out;

	if (action == GET)
		return (pipe_out);
	if (action == SET)
		pipe_out = hold;
	return (pipe_out);
}

/**
 * sigint_mask_act - Takes action on a static bool
 * @action: GET or SET
 * @hold: Value to set in case of SET action
 * @return: The value of the boolean
 */
bool	sigint_mask_act(int action, bool hold)
{
	static bool	mask;

	if (action == SET)
		mask = hold;
	return (mask);
}
