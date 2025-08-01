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

char	*generate_prompt(void)
{
	const char	*temp;
	t_string	str;

	str = string_init();
	temp = environ_get("USER");
	if (temp == NULL)
		temp = "trizawi";
	string_append_cstr(&str, TEXT_BCYAN"(");
	string_append_cstr(&str, temp);
	string_append_cstr(&str, ")[");
	temp = environ_get("PWD");
	if (temp == NULL)
		temp = "???";
	string_append_cstr(&str, temp);
	string_append_cstr(&str, "] (");
	string_append_cstr(&str, ft_itoa(status_get()));
	string_append_cstr(&str, ") $ "TEXT_RESET);
	return (str.buff);
}

/**
 * main - The entry point of the program
 * @ac: Args count
 * @av: Args list
 * @envp: Environment variables as char ** list
 * Return: 0 on success or a non-null value otherwise
 */
int	main(int ac, const char **av, const char **envp)
{
	t_ast	*ast;
	char	*line;

	(void)(ac);
	(void)(av);
	sigint_mask_act(SET, true);
	signal(SIGINT, ft_sigint_handler_prompt);
	signal(SIGQUIT, SIG_IGN);
	environ_init(envp);
	line = ft_readline(generate_prompt());
	while (line)
	{
		set_pipe_in(dup(STDIN_FILENO));
		set_pipe_out(dup(STDOUT_FILENO));
		g_stop_herdoc = false;
		add_history(line);
		ast = ast_create(line);
		exec(ast);
		ft_gc_clear();
		line = ft_readline(generate_prompt());
		close(get_pipe_in());
		close(get_pipe_out());
	}
	ft_clean();
	return (status_get());
}
