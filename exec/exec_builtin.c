# include "./exec.h"
# include "../includes.h"
# include "../libft/libft.h"
# include "./builtins/builtins.h"

int exec_builtin(t_ast *ast)
{
	char	**av;
	int	ac;

	if (ast == NULL)
		return (ERR_NULL);
	if (ast->simple_cmd.argv == NULL)
		return (ERR_NULL);
	av = ast->simple_cmd.argv;
	ac = ast->simple_cmd.argc;
	if (ft_strcmp(av[0], "echo") == SUCCESS)
		return (ft_echo(ac, av));
	if (ft_strcmp(av[0], "cd") == SUCCESS)
		return (ft_cd(ac, av));
	if (ft_strcmp(av[0], "pwd") == SUCCESS)
		return (ft_pwd(ac, av));
	if (ft_strcmp(av[0], "export") == SUCCESS && !is_pipe_next(ast))
		return (ft_export(ac, av));
	if (ft_strcmp(av[0], "unset") == SUCCESS)
		return (ft_unset(ac, av));
	if (ft_strcmp(av[0], "env") == SUCCESS)
		return (ft_env(ac, av));
	if (ft_strcmp(av[0], "exit") == SUCCESS)
		return (ft_exit(ac, av));
	return (SUCCESS);
}
