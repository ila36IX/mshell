/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:23:19 by sboukiou          #+#    #+#             */
/*   Updated: 2025/05/15 13:39:59 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

# define TEXT_RESET "\033[0m"
# define TEXT_BRED "\033[1;31m"
# define TEXT_BACKGROUND_RED "\e[41m"
# define TEXT_BGREEN "\033[1;32m"
# define TEXT_BYELLOW "\033[1;33m"
# define TEXT_BBLUE "\033[1;34m"
# define TEXT_UPURPLE "\e[4;35m"
# define TEXT_UNDERLINE "\033[4m"

#endif
