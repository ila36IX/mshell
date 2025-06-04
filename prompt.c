/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:38:52 by sboukiou          #+#    #+#             */
/*   Updated: 2025/05/15 13:41:04 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

void	prompt(const char *name)
{
	write(STDOUT_FILENO, TEXT_BBLUE, ft_strlen(TEXT_BBLUE));
	write(STDOUT_FILENO, name, ft_strlen(name));
	write(STDOUT_FILENO, TEXT_RESET, ft_strlen(TEXT_RESET));
}
