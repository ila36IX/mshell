#include "print_ast.h"

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
		UNREACHABLE("takes only none-null ast of simple command type!");
	}
	i = 0;
	print_ast_type(ast, indent++);
	_tree_line_prefix(indent, true);
	_tree_line_prefix(indent, false);
	printf("────── %sARGC (%d):%s ", TEXT_UWHITE, ast->simple_cmd->argc,
		TEXT_RESET);
	while (i < (size_t)ast->simple_cmd->argc)
		printf("%s ", ast->simple_cmd->argv[i++]);
	printf("\n");
	_tree_line_prefix(indent, false);
	printf("────── %sI/O (%zu):%s ", TEXT_UWHITE, ast->redir_size, TEXT_RESET);
	print_ast_redirection(ast, indent);
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
		UNREACHABLE("None null ast only!");
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
		UNREACHABLE("takes only none-null ast of subshell type!");
	}
	print_ast_type(ast, indent++);
	_tree_line_prefix(indent, true);
	_print_ast_helper(ast->subshell, indent);
	_print_tree_end_root(indent);
	_tree_line_prefix(indent, false);
	printf("────── %sI/O (%zu):%s ", TEXT_UWHITE, ast->redir_size, TEXT_RESET);
	print_ast_redirection(ast, indent);
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

	if (ast->type == AST_CONNECTOR || !ast)
	{
		UNREACHABLE("None-null ast connector node doesn't have redirection!");
	}
	i = 0;
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
		UNREACHABLE("None null ast only!");
	}
	_print_ast_helper(ast, 0);
	_print_tree_end_root(0);
}
