/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:23:19 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/13 02:30:20 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>

# define TEXT_RESET "\033[0m"

void	child_signal_handler(int sig);
/* Regular Colors */

# define TEXT_BLACK "\033[0;30m"
# define TEXT_RED "\033[0;31m"
# define TEXT_GREEN "\033[0;32m"
# define TEXT_YELLOW "\033[0;33m"
# define TEXT_BLUE "\033[0;34m"
# define TEXT_PURPLE "\033[0;35m"
# define TEXT_CYAN "\033[0;36m"
# define TEXT_WHITE "\033[0;37m"

/* Bold */
# define TEXT_BBLACK "\033[1;30m"
# define TEXT_BRED "\033[1;31m"
# define TEXT_BGREEN "\033[1;32m"
# define TEXT_BYELLOW "\033[1;33m"
# define TEXT_BBLUE "\033[1;34m"
# define TEXT_BPURPLE "\033[1;35m"
# define TEXT_BCYAN "\033[1;36m"
# define TEXT_BWHITE "\033[1;37m"

/* Underline */
# define TEXT_UBLACK "\033[4;30m"
# define TEXT_URED "\033[4;31m"
# define TEXT_UGREEN "\033[4;32m"
# define TEXT_UYELLOW "\033[4;33m"
# define TEXT_UBLUE "\033[4;34m"
# define TEXT_UPURPLE "\033[4;35m"
# define TEXT_UCYAN "\033[4;36m"
# define TEXT_UWHITE "\033[4;37m"

/* Background */
# define TEXT_BG_BLACK "\033[40m"
# define TEXT_BG_RED "\033[41m"
# define TEXT_BG_GREEN "\033[42m"
# define TEXT_BG_YELLOW "\033[43m"
# define TEXT_BG_BLUE "\033[44m"
# define TEXT_BG_PURPLE "\033[45m"
# define TEXT_BG_CYAN "\033[46m"
# define TEXT_BG_WHITE "\033[47m"

# define SUCCESS 0
# define FAIL -1
# define ERR_NULL 1
# define MAX_WD_SIZE 1024
# define SHELL_NAME "minishell"
# define UNSET(var) (void)(var);
# define MARK(str) printf("(%s)(%s) [%s]", __LINE__, __FILE__, str);
#endif
