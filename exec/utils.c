# include "../includes.h"
# include "../parser/parser.h"
# include "../libft/libft.h"

bool	is_builtin(t_ast *ast)
{
	char	**av;

	if (ast == NULL)
		return (false);
	av = ast->simple_cmd.argv;
	if (av == NULL)
		return (printf("NULLED av\n"), false);
	if (ft_strcmp(av[0], "echo") == SUCCESS)
		return (true);
	if (ft_strcmp(av[0], "cd") == SUCCESS)
		return (true);
	if (ft_strcmp(av[0], "pwd") == SUCCESS)
		return (true);
	if (ft_strcmp(av[0], "export") == SUCCESS)
		return (true);
	if (ft_strcmp(av[0], "unset") == SUCCESS)
		return (true);
	if (ft_strcmp(av[0], "env") == SUCCESS)
		return (true);
	if (ft_strcmp(av[0], "exit") == SUCCESS)
		return (true);
	return (false);
}

bool	is_pipe_next(t_ast *ast)
{
	if (!ast)
		return (false);
	if (ast->next)
	{
		ast = ast->next;
		if (ast->type == AST_CONNECTOR)
			if (ast->connector == CONNECTOR_PIPE)
				return (true);
	}
	return (false);
}

bool	is_pipe(t_ast *ast)
{
	if (!ast)
		return (false);
	if (ast->type == AST_CONNECTOR)
		if (ast->connector == CONNECTOR_PIPE)
			return (true);
	return (false);
}
