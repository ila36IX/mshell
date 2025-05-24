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

int	main(void)
{
	char *cmd;
	t_lexer lexer;
	t_token token;

	while (1) {
		cmd = readline("$ ");

		if (!cmd || ft_strcmp(cmd, "exit") == 0)
			break;
		lexer = lexer_new(cmd, ft_strlen(cmd));
		token = lexer_next_token(&lexer);
		while (token.kind)
		{
			print_token(token);
			token = lexer_next_token(&lexer);
		}
		free(cmd);
	}
	return (EXIT_SUCCESS);
}
