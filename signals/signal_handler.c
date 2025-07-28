/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:21:18 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/26 11:21:18 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./signal_handler.h"

bool g_stop_herdoc = false;

void	ft_sigint_handler_herdoc(int signal)
{
	(void) signal;
	g_stop_herdoc = true;
	rl_replace_line("", 0);
	rl_on_new_line();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	ft_sigint_handler_prompt(int signal)
{
	(void) signal;
	g_stop_herdoc = true;
	rl_replace_line("", 0);
	rl_on_new_line();
	ft_putstr_fd("\n", 1);
	rl_redisplay();
	status_set(EXIT_STATUS_SIGINT);
}

void	child_signal_handler(int sig)
{
	if (sig == SIGINT)
		exit(EXIT_STATUS_SIGINT);
}
