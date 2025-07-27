/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:10:39 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:10:43 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes.h"
#include "./environ.h"
#include "../status.h"

int	ft_pwd(void)
{
	char		current_working_dir[MAX_WD_SIZE];
	const char	*current_dir_env;
	int			status;

	status = EXIT_SUCCESS;
	current_dir_env = environ_get("PWD");
	if (current_dir_env)
	{
		printf("%s\n", current_dir_env);
		return (status_set(status), status);
	}
	else if (getcwd(current_working_dir, MAX_WD_SIZE) == SUCCESS)
	{
		printf("%s\n", current_working_dir);
		return (status_set(status), status);
	}
	status = EXIT_FAILURE;
	return (status_set(status), status);
}
