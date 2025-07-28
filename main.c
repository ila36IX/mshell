/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 02:11:02 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/28 02:11:03 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"
#include "./parser/parser.h"
#include "./exec/status.h"
#define PROMPT "\033[0;33m[User@Debian]$ \033[0m"

int	main(int ac, const char **av, const char **envp)
{
	t_ast	*ast;
	char	*line;
	int		status;

	(void)(ac);
	(void)(av);
	signal(SIGINT, ft_sigint_handler_prompt);
	environ_init(envp);
	line = ft_readline(PROMPT);
	while (line)
	{
		g_stop_herdoc = false;
		add_history(line);
		ast = ast_create(line);
		exec(ast);
		ft_gc_clear();
		line = ft_readline(PROMPT);
	}
	ft_gc_clear();
	environ_free();
	status = status_get();
	return (status);
}
