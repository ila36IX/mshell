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
#include "types.h"

void	print_ast_simple_cmd(int indenet_level, char *str);

void	debug_ast(t_ast *ast);
t_ast	*new_ast(void)
{
	t_ast *ast, *ast1, *ast2, *ast3;

	ast = malloc(sizeof(t_ast));
	ast->type = AST_SIMPLE_COMMAND;
	ast->simple_cmd = malloc(sizeof(t_simple_cmd));
	ast->simple_cmd->argv = ft_split("ls -la file1 file2 file3", ' ');
	ast->simple_cmd->argc = 5;
	ast->redir = malloc(sizeof(t_redirect) * 2);
	ast->redir[0].type = REDIR_TYPE_APPEND;
	ast->redir[0].target = "file1";
	ast->redir[1].type = REDIR_TYPE_HEREDOC;
	ast->redir[1].target = "eof";
	ast->redir_size = 2;

	ast1 = malloc(sizeof(t_ast));
	ast->next = ast1;
	ast1->type = AST_SIMPLE_COMMAND;
	ast1->simple_cmd = malloc(sizeof(t_simple_cmd));
	ast1->simple_cmd->argv = ft_split("ls -la file1 file2 file3", ' ');
	ast1->simple_cmd->argc = 5;
	ast1->redir = malloc(sizeof(t_redirect) * 2);
	ast1->redir[0].type = REDIR_TYPE_APPEND;
	ast1->redir[0].target = "file1";
	ast1->redir[1].type = REDIR_TYPE_HEREDOC;
	ast1->redir[1].target = "eof";
	ast1->redir_size = 2;

	ast2 = malloc(sizeof(t_ast));
	ast1->next = ast2;
	ast2->type = AST_SIMPLE_COMMAND;
	ast2->simple_cmd = malloc(sizeof(t_simple_cmd));
	ast2->simple_cmd->argv = ft_split("ls -la file1 file2 file3", ' ');
	ast2->simple_cmd->argc = 5;
	ast2->redir = malloc(sizeof(t_redirect) * 2);
	ast2->redir[0].type = REDIR_TYPE_APPEND;
	ast2->redir[0].target = "file1";
	ast2->redir[1].type = REDIR_TYPE_HEREDOC;
	ast2->redir[1].target = "eof";
	ast2->redir_size = 2;

	ast3 = malloc(sizeof(t_ast));
	ast2->next = ast3;
	ast3->type = AST_CONNECTOR;
	ast3->connector = CONNECTOR_AND;
	ast3->next = NULL;
	return (ast);
}
int	main(void)
{
	t_ast *ast;

	ast = new_ast();
	debug_ast(ast);
	return (EXIT_SUCCESS);
}
