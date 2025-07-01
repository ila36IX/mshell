# include "./builtins.h"
#include "environ.h"

/**
 * Executes a built-in command
 * @ast: Ast structure
 * Return: Exit status of the given command
 */
int	exec_builtin(t_ast *ast)
{
	t_simple_cmd	cmd;

	cmd = ast->simple_cmd;
	if (ft_strcmp(cmd.argv[0], "echo") == 0)
		return (echo(cmd.argv));
	else if (ft_strcmp(cmd.argv[0], "cd") == 0)
			return (cd(cmd.argc, cmd.argv));
	else if (ft_strcmp(cmd.argv[0], "pwd") == 0)
			return (pwd());
	else if (ft_strcmp(cmd.argv[0], "exit") == 0)
					quit(cmd.argv, cmd.argc);
	else if (ft_strcmp(cmd.argv[0], "export") == 0)
					return (bin_export(cmd));
	else if (ft_strcmp(cmd.argv[0], "env") == 0)
		return (environ_print());
	else if (ft_strcmp(cmd.argv[0], "unset") == 0)
		  return (environ_unset(cmd.argv[1]));
	return (0);
}
