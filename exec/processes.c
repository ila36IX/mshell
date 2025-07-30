/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:14:14 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/28 02:18:43 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"

#define MAX_PID_COUNT 1024

/**
 * last_pid_act - Takes action
 * on a pid stored variable
 * @action: Sets or gets the value
 * of the pid
 * @value: value to assign in case
 * of a SET action
 * Return: The value of the pid
 */
static int	last_pid_act(int action, int value)
{
	static pid_t	last_pid;

	if (action == CLEAN)
		last_pid = FAIL;
	else if (action == SET)
		last_pid = value;
	return (last_pid);
}

/**
 * pid_push -  Sets the value of 
 * last_pid to a given value
 * @pid: Value to keep
 * Return: The pid itself
 */
int	pid_push(pid_t pid)
{
	last_pid_act(SET, pid);
	return (pid);
}

/**
 * pid_get -  gets_the last pid in pipline
 * value
 * Return: The last pid value
 */
pid_t	pid_get(void)
{
	return (last_pid_act(GET, 0));
}

/**
 * pid_wait_all - Waits for all children
 * processes and stores the exit status of
 * the last one
 */
int	pid_wait_all(void)
{
	int	status;

	waitpid(last_pid_act(GET, SUCCESS), &status, 0);
	last_pid_act(CLEAN, FAIL);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (WEXITSTATUS(status));
}
