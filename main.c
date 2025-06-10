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

#include "main.h"

int	main(int ac, char **av)
{
	t_ast	*ast;
	char	*cmd;

	UNSET(ac);
	UNSET(av);
	UNSET(ast);
	while (true)
	{
		cmd = readline("[minishell]$ ");
		ft_gcadd_back(cmd);
		if (cmd == NULL)
		{
			ft_gc_clear();
			exit(0);
		}
		printf("%s\n", cmd);
		ft_gc_clear();
	}
	return (EXIT_SUCCESS);
}
