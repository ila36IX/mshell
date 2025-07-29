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

bool	g_stop_herdoc = false;

/**
 	* ft_sigint_handler_herdoc - Handles the SIGINT (CTRL-C)
 	* signal for the herdoc reading process
	* @signal: The number of the signal received
 */
void	ft_sigint_handler_herdoc(int signal)
{
	(void) signal;
	g_stop_herdoc = true;
	rl_replace_line("", 0);
	rl_on_new_line();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

/**
 	* ft_sigint_handler_prompt - Handles the SIGINT (CTRL-C)
 	* signal for the parent process
	* @signal: The number of the signal received
 */
void	ft_sigint_handler_prompt(int signal)
{
	bool	mask;

	(void) signal;
	g_stop_herdoc = true;
	mask = sigint_mask_act(GET, false);
	if (mask == true)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		ft_putstr_fd("\n", 1);
		rl_redisplay();
		status_set(EXIT_STATUS_SIGINT);
	}
	else
		ft_putstr_fd("\n", 1);
}

/**
 	* child_signal_handler - Handles the SIGINT and SIGQUIT
 	* signals for the children processes
	* @signal: The number of the signal received
 */
void	child_signal_handler(int sig)
{
	if (sig == SIGINT)
		exit(EXIT_STATUS_SIGINT);
	else if (sig == SIGQUIT)
		exit(EXIT_STATUS_SIGQUIT);
}
