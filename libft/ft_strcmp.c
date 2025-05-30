/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 03:00:44 by aljbari           #+#    #+#             */
/*   Updated: 2025/03/12 03:02:47 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * ft_strcmp - compare two strings
 *
 * @s1: String
 * @s2: String
 *
 * Return: Return 0 if the two strings are identical
 * none-zero if diff exists
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)--s2);
}
