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

void	print_ast_simple_cmd(int indenet_level, char *str);

void	debug_ast(t_ast *ast);
t_ast	*new_ast(void)
{
	t_ast *ast;

	ast = malloc(sizeof(t_ast));
	ast->type = AST_SIMPLE_COMMAND;
	ast->simple_cmd = malloc(sizeof(t_simple_cmd));
	ast->simple_cmd->argv = ft_split("ls -la file1 file2 file3", ' ');
	ast->simple_cmd->argc = 5;
	ast->redir = malloc(sizeof(t_redirect));
	ast->redir->type = REDIR_TYPE_APPEND;
	ast->redir->target = "file1";
	ast->redir_size = 1;
	return (ast);
}
int	main(void)
{
	t_ast *ast;

	ast = new_ast();
	debug_ast(ast);
	return (EXIT_SUCCESS);
}
