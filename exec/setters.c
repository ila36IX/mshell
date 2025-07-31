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

/**
 * set_pipe_in - Sets the value for pipe_in
 * @value: Value to set
 * Return: The value itself
 */
int	set_pipe_in(int value)
{
	return (pipe_in_act(SET, value));
}

/**
 * set_pipe_out - Sets the value for pipe_in
 * @value: Value to set
 * Return: The value itself
 */
int	set_pipe_out(int value)
{
	return (pipe_out_act(SET, value));
}
