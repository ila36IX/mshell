/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <aljbari@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 15:18:51 by aljbari           #+#    #+#             */
/*   Updated: 2025/01/27 00:44:23 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

/**
	* is_delim - Checks if a char is a delimiter or not
	* @c: Char to check
	* Return: 1 if it is a delimiter , 0 otherwise
*/

static int	is_delim(char c)
{
	if (c == ' ' || c == '\r' || c == '\f')
		return (1);
	if (c == '\t' || c == '\v' || c == '\n')
		return (1);
	return (0);
}

int	valid_number(char digit, long num, int sign)
{
	if (digit)
		return (-1);
	return (num * sign);
}

/**
	* ft_atoi - Converts a valid alphanumerical string into an integer literal
	* @nptr: Alphanum string to convert
	* Return: An int depending on the nptr
*/
int	ft_atoi(const char *nptr)
{
	int		count;
	int		sign;
	long	num;

	count = 0;
	while (is_delim(nptr[count]) && nptr[count])
		count++;
	sign = 1;
	if (nptr[count] == '-')
	{
		sign = -1;
		count++;
	}
	else if (nptr[count] == '+')
		count++;
	num = 0;
	if (!ft_isdigit(nptr[count]))
		return (-1);
	while (ft_isdigit(nptr[count]) && nptr[count])
	{
		num = (num * 10) + nptr[count++] - '0';
		if (num > INT_MAX)
			return (-1);
	}
	return (valid_number(nptr[count], num, sign));
}
