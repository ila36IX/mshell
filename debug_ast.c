#include "includes.h"
#include "main.h"
#include "types.h"


const char	*ast_type_to_str(t_ast_type type) 
{
	if (type == AST_CONNECTOR)
		return ("CONNECTOR");
	else if (type == AST_SUBSHELL)
		return ("SUBSHELL");
	else if (type == AST_SIMPLE_COMMAND)
		return ("SIMPLE COMMAND");
	else
		UNREACHABLE("ast type string represenation needed!");
}

const char *connector_type_to_str(t_connector type)
{
	if (type == CONNECTOR_AND)
		return ("AND");
	else if (type == CONNECTOR_OR)
		return ("OE");
	else if (type == CONNECTOR_PIPE)
		return ("PIPE");
	else 
		UNREACHABLE("Unknown connector type!");

}

#define INDENT_SIZE 8

void	tree_line_prefix(int indent, bool is_empty_line)
{
	int i;

	i = 0;
	while (i < indent)
	{
		if (i + 1 == indent && is_empty_line == false)
			printf("%*s├", INDENT_SIZE, "");
		else
			printf("%*s│", INDENT_SIZE, "");
		i++;
	}
	if (is_empty_line)
		printf("\n");
}

void	print_tree_last_line(int indent)
{
	int i;

	i = 0;
	while (i < indent)
	{
		printf("%*s╰", INDENT_SIZE, "");
		i++;
	}
	printf("\n");
}

void	print_ast_type(int indenet_level, t_ast *ast)
{
	int i = 0;

	i = 0;
	tree_line_prefix(indenet_level, false);
	printf("%s", TEXT_BGREEN);
	if (ast->type == AST_CONNECTOR)
		printf("◯───── %s(%s)\n", ast_type_to_str(ast->type), connector_type_to_str(ast->connector));
	else
		printf("◯───── %s\n", ast_type_to_str(ast->type));
	printf("%s", TEXT_RESET);
}

const char *redir_type_to_str(t_redirect_type type)
{
	if (type == REDIR_TYPE_IN)
		return ("<");
	else if (type == REDIR_TYPE_OUT)
		return (">");
	else if (type == REDIR_TYPE_HEREDOC)
		return (">>");
	else if (type == REDIR_TYPE_APPEND)
		return (">>");
	else
		UNREACHABLE("Unknown redirect type!");
}


void	print_simple_cmd(int indent, t_ast *ast)
{
	size_t i;

	i = 0;
	print_ast_type(indent++, ast);
	tree_line_prefix(indent, true);
	tree_line_prefix(indent, false);
	printf("────── %sARGC (%d):%s ",  TEXT_UWHITE, ast->simple_cmd->argc, TEXT_RESET);
	while (i < (size_t) ast->simple_cmd->argc)
		printf("%s ", ast->simple_cmd->argv[i++]);
	printf("\n");
	tree_line_prefix(indent, false);
	printf("────── %sI/O (%zu):%s ",  TEXT_UWHITE, ast->redir_size, TEXT_RESET);
	i = 0;
	while (i < ast->redir_size)
	{
		if (i % 2)
			printf("%s", TEXT_BYELLOW);
		else
			printf("%s", TEXT_BBLUE);
		printf("%s '%s'%s ", redir_type_to_str(ast->redir[i].type), ast->redir[i].target, TEXT_RESET);
		i++;
	}
	printf("\n");
	tree_line_prefix(indent, true);
}

void	print_ast_connector(int indent, t_ast *ast)
{
	size_t i;

	i = 0;
	print_ast_type(indent++, ast);
	tree_line_prefix(indent, true);
}

void	debug_ast(t_ast *ast)
{
	int indent;
	char *text[2];

	text[1] = NULL;
	indent = 0;
	while (ast)
	{
		if (ast->type == AST_SIMPLE_COMMAND)
			print_simple_cmd(indent, ast);
		else if (ast->type == AST_CONNECTOR)
			print_ast_connector(indent, ast);
		ast = ast->next;
	}
	print_tree_last_line(indent + 1);
}
