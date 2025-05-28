#include "main.h"
#include "types.h"


char	*ast_type_to_str(t_ast_type type) 
{
	if (type == AST_CONNECTOR)
		return ("connector");
	else if (type == AST_SUBSHELL)
		return ("subshell");
	else if (type == AST_SIMPLE_COMMAND)
		return ("simple command");
	else
		UNREACHABLE("ast type string represenation needed!");
}
#define INDENT_SIZE 8

void	print_ast_type(int indenet_level, char *str, char *style)
{
	int i = 0;

	while (i < indenet_level)
	{
		printf("%*s│", INDENT_SIZE, "");
		i++;
	}
	printf("\n");
	i = 0;
	while (i < indenet_level)
	{
		if (i + 1 == indenet_level)
			printf("%*s├", INDENT_SIZE, "");
		else
			printf("%*s│", INDENT_SIZE, "");
		i++;
	}
	printf("────── %s%s%s\n", style ? style : "", str, TEXT_RESET);
}

void	print_simple_cmd(int indnet_level, t_ast *ast)
{
	int i = 0;
	print_ast_type(indnet_level, "SIMPLE COMMAND", TEXT_UNDERLINE);

	indnet_level++;
	while (i < indnet_level)
	{
		printf("%*s│", INDENT_SIZE, "");
		i++;
	}
	printf("\n");
	i = 0;
	while (i < indnet_level)
	{
		if (i + 1 == indnet_level)
			printf("%*s├", INDENT_SIZE, "");
		else
			printf("%*s│", INDENT_SIZE, "");
		i++;
	}
	printf("────── ARGS (%d): ",  ast->simple_cmd->argc);
	for (int i = 0; i < ast->simple_cmd->argc; i++)
		printf("%s ", ast->simple_cmd->argv[i]);
	printf("\n");
	i = 0;
	while (i < indnet_level)
	{
		if (i + 1 == indnet_level)
			printf("%*s├", INDENT_SIZE, "");
		else
			printf("%*s│", INDENT_SIZE, "");
		i++;
	}
	printf("────── I/O (%zu): ",  ast->redir_size);
	for (size_t i = 0; i < ast->redir_size; i++)
		printf("%s ", ast->redir[i].target);
	printf("\n");
}

void	debug_ast(t_ast *ast)
{
	int indent_lvl;
	char *text[2];

	text[1] = NULL;
	indent_lvl = 0;
	if (ast->type == AST_SIMPLE_COMMAND)
	{
		print_simple_cmd(indent_lvl, ast);
	}
}
