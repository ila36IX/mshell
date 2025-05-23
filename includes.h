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

# define MAX_REDIRECTIONS 200
# define RESET "\033[0m"
# define BRED "\033[1;31m"
# define BACKGROUND_RED "\e[41m"
# define BGREEN "\033[1;32m"
# define BYELLOW "\033[1;33m"
# define BBLUE "\033[1;34m"
# define UPURPLE "\e[4;35m"

#endif
