/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: username <your@email.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 22:35:30 by username          #+#    #+#             */
/*   Updated: 2025/03/03 04:35:27 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr_ptr(char const *start, char const *end)
{
	size_t	len;
	char	*str;
	size_t	i;

	if (!start || !end || end < start)
		return (NULL);
	len = end - start + 1;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
		str[i++] = *start++;
	str[len] = '\0';
	return (str);
}
