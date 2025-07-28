/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 11:28:22 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/26 11:28:22 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_readline(const char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
		return (NULL);
	ft_gcadd_back(line);
	return (line);
}
