# include "./exec.h"


int exec_node(t_ast *ast)
{
	int	status;

	status = 0;
	if (ast == NULL)
		return (ERR_NULL);
	/* setup_gates(ast);
	if (ast->type == AST_SUBSHELL)
		status = exec_subshell(ast);
	else if (ast->type == AST_SIMPLE_COMMAND)
		status = exec_simple_command(ast);
	reset_gates(ast); */

	return (status);
}
