# include "./main.h"

# define BUILTIN 0
# define PRECOMPILED 1
# define NOT_FOUND 2

# include <sys/stat.h>

int	exec_builtin(char **av, t_redirect *redir, t_list *env)
{
	if (ft_strcmp(av[0], "echo") == 0)
		return (echo(av, redir, env));
	/*else if (ft_strcmp(av[0], "cd") == 0)*/
	/*		cd(av, redir);*/
	/*else if (ft_strcmp(av[0], "pwd") == 0)*/
	/*		pwd(redir);*/
	/*else if (ft_strcmp(av[0], "export") == 0)*/
	/*				export(av, redir);*/
	/*else if (ft_strcmp(av[0], "unset") == 0)*/
	/*	  unset(av, redir);*/
	/*else if (ft_strcmp(av[0], "env") == 0)*/
	/*	  env(redir);*/
	/*else if (ft_strcmp(av[0], "exit") == 0)*/
	/*				exit(av);*/
	return (0);
}

/**
 * check_command_type - Checks for the type of given command by name
 * @name: A string given as comman name (EX: ls)
 * Return: Type of the given command or NOT_FOUND for invalid names
 */
int	check_command_type(char *name)
{
	struct	stat	file_data;

	if (!name)
		return (NOT_FOUND);
	if (ft_strcmp(name, "echo") == 0)
			return (BUILTIN);
	else if (ft_strcmp(name, "cd") == 0)
			return (BUILTIN);
	else if (ft_strcmp(name, "pwd") == 0)
			return (BUILTIN);
	else if (ft_strcmp(name, "export") == 0)
			return (BUILTIN);
	else if (ft_strcmp(name, "unset") == 0)
			return (BUILTIN);
	else if (ft_strcmp(name, "env") == 0)
			return (BUILTIN);
	else if (ft_strcmp(name, "exit") == 0)
			return (BUILTIN);
	else if (stat(name, &file_data) == 0 && file_data.st_mode == S_IXUSR)
		return (PRECOMPILED);
	return (NOT_FOUND);
}

/**
 * exec_simple_cmd - Executes a simple command with
 * arguments and redirections
 * @cmd: Command to execute with its meta-data
 * @redir: Redirection information (files, and streams)
 * Return: Exit status of the cmd
 */
int	exec_simple_cmd(t_ast *ast, t_list *env)
{
	t_simple_cmd	cmd;

	if (!ast || !env)
		return (EXIT_FAILURE);
	cmd = ast->simple_cmd;
	if (check_command_type(cmd.argv[0]) == BUILTIN)
		exec_builtin(cmd.argv, ast->redir, env);
	else
		return (0);
	/*else if (check_command_type(cmd.argv[0]) == PRECOMPILED)*/
	/*	exec_precompiled(cmd->argv, ast->redir, env);*/
	return (0);
}

/**
 	* exec_main - main execution function that takes the ast
	* @ast: Ast data
	* @return: Exit status of the given command
 */
int exec_main(t_ast *ast, char **envp)
{
	int	status;
	t_list	*env;

	status = 0;
	if (!ast)
		return (EXIT_FAILURE);
	env = env_init(envp);
	if (!envp)
		return (EXIT_FAILURE);
	if (ast->type == AST_SIMPLE_COMMAND)
		return (exec_simple_cmd(ast, env));
	/*else if (ast->type == AST_SUBSHELL)*/
	/*		return (main_exec(ast->subshell, env));*/
	/*else if (ast->type == AST_CONNECTOR)*/
	/*		return (exec_connector(ast->prev, ast->next, env));*/
	else
		UNIMPLEMENTED("It shouldn't get here. AST type is invalid\n");
	return (status);
}
