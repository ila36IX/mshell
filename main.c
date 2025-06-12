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

#include "ast_print.h"
#include "lexer.h"
#include "main.h"
#include "parser.h"
#include "types.h"

bool	ast_print_error(t_ast *ast);

int	main(void)
{
	t_ast	*ast;
	char	*line;
	t_lexer	lexer;

	while ((line = readline("$ ")))
	{
		lexer = lexer_new(line, ft_strlen(line));
		ast = create_ast(&lexer);
		if (ast_print_error(ast) == false)
			print_ast(ast);
	}
}
