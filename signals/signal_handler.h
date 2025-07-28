/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hadler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:32:18 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/26 11:32:18 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SIGNAL_HANDLER_H
# define SIGNAL_HANDLER_H
# include "../includes.h"
# include "../exec/exec.h"
# include "../libft/libft.h"
# define EXIT_STATUS_SIGINT 130

void	ft_sigint_handler_herdoc(int signal);
void	ft_sigint_handler_prompt(int signal);
void	child_signal_handler(int sig);
extern bool	g_stop_herdoc;

#endif
