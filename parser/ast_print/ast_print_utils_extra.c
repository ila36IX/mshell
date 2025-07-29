/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_print_utils_extra.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 00:45:31 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/29 00:45:31 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast_print.h"

/**
 * print_ast_subshell - print ast node of type subshell, if it contains more
 * subshells they will be printed recursively
 *
 * @ast: pointer to ast node
 * @indent: give it 0 if your not printing a tree
 * Return: Noting
 */
void	print_ast_subshell(t_ast *ast, int indent)
{
	if (ast->type != AST_SUBSHELL || !ast)
	{
		return ;
	}
	print_ast_type(ast, indent++);
	_tree_line_prefix(indent, true);
	if (ast->subshell)
	{
		_print_ast_helper(ast->subshell, indent);
		_print_tree_end_root(indent);
	}
	else
	{
		_tree_line_prefix(indent, false);
		printf("────── %s EMPTY_SUBSHELL%s\n", TEXT_BRED, TEXT_RESET);
		_tree_line_prefix(indent, true);
	}
	_tree_line_prefix(indent, false);
	printf("────── %sSUBSHELL I/O (%zu):%s ", TEXT_UWHITE, ast->redir_size,
		TEXT_RESET);
	print_ast_redirection(ast, indent);
	_tree_line_prefix(indent, false);
	printf("────── %sSUBSHELL I/O TOKENS (%zu):%s ", TEXT_UWHITE,
		ast->redir_size, TEXT_RESET);
	print_ast_redir_tokens(ast, indent);
}

/**
 * print_ast_redirection - print ast I/O redirections
 *
 * @ast: Pointer to none-null ast node
 * @indent: give it 0 if your not printing a tree
 * Return: Nothing
 */
void	print_ast_redirection(t_ast *ast, int indent)
{
	size_t	i;

	(void)indent;
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
		printf("%s '%s'%s ", redir_type_to_str(ast->redir[i].type),
			ast->redir[i].target, TEXT_RESET);
		i++;
	}
	printf("\n");
}
