# include "./exec.h"
# define PIPE_SIZE 2


int	exec(t_ast *ast)
{
	if (ast == NULL)
		return (ERR_NULL);
	while (ast)
	{
		if (ast->type == AST_SIMPLE_COMMAND)
		{
			exec_simple_command(ast);
			while (ast && (ast->type == AST_SIMPLE_COMMAND || is_pipe(ast)))
				ast =  ast->next;
		}
		if (ast)
			ast = ast->next;
	}
	while (waitpid(-1, NULL, 0) > 0)
		;
	return (SUCCESS);
}
