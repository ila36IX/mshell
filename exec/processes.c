/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:14:14 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:14:14 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./exec.h"
#include "../libft/libft.h"

#define MAX_PID_COUNT 1024

static int	last_pid_act(int action, int value)
{
	static pid_t	last_pid;

	if (action == CLEAR)
		last_pid = FAIL;
	else if (action == SET)
		last_pid = value;
	return (last_pid);
}

int	pid_count_act(int action, int hold)
{
	static int	pid_count;

	if (action == GET)
		return (pid_count);
	if (action == SET)
		pid_count = hold;
	return (pid_count);
}

int	pid_push(pid_t pid)
{
	last_pid_act(SET, pid);
	return (pid);
}

int	pid_wait_all(void)
{
	int	status;

	waitpid(last_pid_act(GET, SUCCESS), &status, 0);
	return (WEXITSTATUS(status));
}
