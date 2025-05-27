/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:36:59 by sboukiou          #+#    #+#             */
/*   Updated: 2025/05/15 13:41:32 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

# define PROMPT BYELLOW"[sboukiou@debian ~]"BBLUE"$ "RESET


/**
	 * get_cmd_type - Returns the type a builtin command based on a string
	 * @: string to check
	 * Return: Type of builtin corresponding or INVALID otherwise
 */

t_builtin_type	get_cmd_type(const char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (ECHO);
	if (ft_strcmp(cmd, "exit") == 0)
		return (EXIT);
	return (INVALID);
}

/**
	* main - The main function - Entry point of the program
	* @argc: Number of command-line provided arguments for the program
	* @argv: Strings-array of arguments
	* @envp: Strings-array of environment variables
	* Return: EXIT_SUCCESS (0) if succeeded | A costum failure status is used otherwise
*/

int	main(void)
{
	char *cmd;
	do {
		cmd = readline(PROMPT);
		echo(cmd, true);
		free(cmd);
	} while (cmd != NULL);
	if (cmd)
		free(cmd);
	return (EXIT_SUCCESS);
}
