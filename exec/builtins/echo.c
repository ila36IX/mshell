/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:08:55 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:09:32 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes.h"
#include "../status.h"
#include "../../libft/libft.h"

/**
 * is_option - Checks if
 * a given string is an option
 * @opt: String to check on
 * Return: True it is, false otherwise
 */
bool	is_option(const char *opt)
{
	int	i;

	if (opt == NULL)
		return (ERR_NULL);
	if (ft_strlen(opt) == 1)
		return (false);
	i = 0;
	if (opt[i++] != '-')
		return (false);
	while (opt[i])
	{
		if (opt[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

/**
	* ft_echo - Mimics the behavior of the echo command
	* writes the given arguemnt/text to STDOUT
	* @ac: Number of provided arguments
	* @av: Args provided
	* Return: Number of bytes written or EXIT_FAILURE (1) instead
*/
int	ft_echo(int ac, char **av)
{
	int		i;
	bool	newline;

	if (av == NULL)
		return (status_set(ERR_NULL), ERR_NULL);
	if (ac == 1)
		return (printf("\n"), status_set(SUCCESS), SUCCESS);
	i = 1;
	newline = true;
	while (av[i] && is_option(av[i]) == true)
	{
		newline = false;
		i++;
	}
	while (av[i])
	{
		printf("%s", av[i]);
		if (av[i + 1])
			printf(" ");
		i++;
	}
	if (newline == true)
		printf("\n");
	return (SUCCESS);
}
