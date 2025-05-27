# include "../includes.h"
# include "../types.h"
# include "../lexer.h"

 /*Yet to be implemented */
size_t	exec_subshell(t_ast *subshell);
size_t	exec_simple_command(t_simple_cmd *cmd);
size_t	exec_connector(t_connector, t_ast *next_cmd);


/**
	* execution - Executes a command based on its ast
	* @ast: asbstrac-syntax-tree holding the cmd meta-data
	* Return: Status with which the command executed
*/

size_t	execution(t_ast *ast)
{
	if (!ast)
		return (EXIT_FAILURE);
	while (ast)
	{
		if (ast->type == AST_SUBSHELL)
			exec_subshell(ast->subshell);
		else if (ast->type == AST_SIMPLE_COMMAND)
			exec_simple_command(ast->simple_cmd);
		else if (ast->type == AST_CONNECTOR)
			exec_connector(ast->connecter, ast->next);
		ast = ast->next;
	}
		return (EXIT_SUCCESS);
}
