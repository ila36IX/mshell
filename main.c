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
#include "./exec/builtins/environ.h"
#include "string.h"
#include "parser.h"
#include "ast_print.h"

bool	ast_print_error(t_ast *ast);



int	main(void)
{
	char	*line;
	t_ast *ast;
	t_lexer lexer;

	environ_set("var", "test");
	environ_set("Apple", "MacOS");
	environ_set("foo", "bar");
	environ_set("a", "@");
	environ_set("A", "%");
	environ_set("Harry", "Potter");
	environ_set("_Harry", "_Potter");
	environ_set("hassan", "gay");
	environ_set("who", "I AM LORD VOLDEMORT!");
	environ_set("spaces", "file1 file2");
	environ_print();
	while ((line = readline("$ ")))
	{
		lexer = lexer_new(line, ft_strlen(line));
		ast = create_ast(&lexer);
		print_ast(ast);
	}
	return (0);
}
