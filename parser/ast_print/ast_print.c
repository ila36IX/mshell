/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:03:51 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/03 19:04:06 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_print.h"

void	print_ast_simple_helper(t_ast *ast, int indent)
{
	size_t	i;

	printf("\n");
	_tree_line_prefix(indent, false);
	printf("────── %sARGS (%ld):%s ", TEXT_UWHITE, ast->simple_cmd.argc,
		TEXT_RESET);
	i = 0;
	while (i < (size_t)ast->simple_cmd.argc)
		printf("'%s' ", ast->simple_cmd.argv[i++]);
	printf("\n");
	_tree_line_prefix(indent, false);
	printf("────── %sI/O (%zu):%s ", TEXT_UWHITE, ast->redir_size, TEXT_RESET);
	print_ast_redirection(ast, indent);
	_tree_line_prefix(indent, false);
	printf("────── %sI/O TOKENS (%zu):%s ", TEXT_UWHITE, ast->redir_size,
		TEXT_RESET);
	print_ast_redir_tokens(ast, indent);
}

/**
 * print_ast_simple_cmd - print ast simple command, with its I/O redirections
 *
 * @indent: give it 0 if you're not printing a tree
 * Return: Noting
 */
void	print_ast_simple_cmd(t_ast *ast, int indent)
{
	size_t	i;

	if (ast->type != AST_SIMPLE_COMMAND || !ast)
	{
		return ;
	}
	i = 0;
	print_ast_type(ast, indent++);
	_tree_line_prefix(indent, true);
	_tree_line_prefix(indent, false);
	printf("────── %sARG_TOKENS (%ld):%s ", TEXT_UWHITE,
		ast->simple_cmd.tok_argv.length, TEXT_RESET);
	while (i < (size_t)ast->simple_cmd.tok_argv.length)
	{
		printf("'%.*s' ", (int)ast->simple_cmd.tok_argv.buff[i].len,
			ast->simple_cmd.tok_argv.buff[i].text);
		i++;
	}
	print_ast_simple_helper(ast, indent);
}

/**
 * print_ast_type - print type of an ast node
 *
 * @ast: Pointer to ast node
 * @indent: give it 0 if your not printing a tree
 * Return: Noting
 */
void	print_ast_type(t_ast *ast, int indent)
{
	if (!ast)
	{
		return ;
	}
	_tree_line_prefix(indent, false);
	printf("%s", TEXT_BGREEN);
	if (ast->type == AST_CONNECTOR)
	{
		printf("◯───── %s(%s)\n", ast_type_to_str(ast->type),
			connector_type_to_str(ast->connector));
	}
	else
		printf("◯───── %s\n", ast_type_to_str(ast->type));
	printf("%s", TEXT_RESET);
}

/**
 * print_ast_redirection - print ast I/O redirections
 *
 * @ast: Pointer to none-null ast node
 * @indent: give it 0 if your not printing a tree
 * Return: Nothing
 */
void	print_ast_redir_tokens(t_ast *ast, int indent)
{
	size_t	i;
	t_word	word;

	if (ast->type == AST_CONNECTOR || !ast)
	{
		return ;
	}
	i = 0;
	if (ast->redir_size == 0)
		printf("(nil)");
	while (i < ast->redir_size)
	{
		if (i % 2)
			printf("%s", TEXT_BYELLOW);
		else
			printf("%s", TEXT_BBLUE);
		word = ast->redir[i].word_target;
		printf("%s '%.*s'%s ", redir_type_to_str(ast->redir[i].type),
			(int)word.len, word.text, TEXT_RESET);
		i++;
	}
	printf("\n");
	_tree_line_prefix(indent, true);
}

/**
 * print_ast - Enjoy a nice view of your beautiful ast
 *
 * @ast: Pointer to none-null ast node
 * Return: Nothing
 */
void	print_ast(t_ast *ast)
{
	if (!ast)
	{
		printf("Empty ast\n");
		return ;
	}
	_print_ast_helper(ast, 0);
	_print_tree_end_root(0);
}
