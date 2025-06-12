/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:36:59 by sboukiou          #+#    #+#             */
/*   Updated: 2025/05/15 13:41:32 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "execution/builtins/builtins.h"

# define BUILTIN 0
# define PRECOMPILED 1
# define NOT_FOUND 2

# include <sys/stat.h>

int	exec_builtin(char **av, t_redirect *redir, t_list *env)
{
	if (ft_strcmp(av[0], "echo") == 0)
		echo(av, redir, env);
	else if (ft_strcmp(av[0], "cd") == 0)
			cd(av, redir);
	else if (ft_strcmp(av[0], "pwd") == 0)
			pwd(redir);
	else if (ft_strcmp(av[0], "export") == 0)
					export(av, redir);
	else if (ft_strcmp(av[0], "unset") == 0)
		  unset(av, redir);
	else if (ft_strcmp(av[0], "env") == 0)
		  env(redir);
	else if (ft_strcmp(av[0], "exit") == 0)
					exit(av);
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
int	exec_simple_cmd(t_simple_cmd *cmd, t_redirect *redir,t_list *env)
{
	int	i;

	if (!cmd)
		return (EXIT_FAILURE);
	i = 0;
	if (check_command_type(cmd->argv[0]) == BUILTIN)
		exec_builtin(cmd->argv, cmd->redir, env);
	else if (check_command_type(cmd->argv[0]) == PRECOMPILED)
		exec_precompiled(cmd->argv, cmd->redir, env);

}

/**
 	* main_exec - main execution function that takes the ast
	* @ast: Ast data
	* @return: Exit status of the given command
 */
int	main_exec(t_ast *ast, t_list *env)
{
	if (!ast)
		return (EXIT_FAILURE);
	if (ast->type == AST_SIMPLE_COMMAND)
		return (exec_simple_cmd(ast->simple_cmd, ast->redir, env));
	else if (ast->type == AST_SUBSHELL)
			return (main_exec(ast->subshell, env));
	else if (ast->type == AST_CONNECTOR)
			return (exec_connector(ast->prev, ast->next, env));
	else
		UNIMPLEMENTED("It shouldn't get here. AST type is invalid\n");
	return (0);
}

/**
	* main - Main function / Entry point
	* @ac: Args count
	* @av: Args as a char * array
	* @envp: Env variables
	* Return: 0 on SUCCESS or non-null value otherwise
*/
int	main(int ac, char **av, char **envp)
{
	t_ast	*ast;
	char	*cmd;
	t_list	*env;

	UNSET(ac);
	UNSET(av);
	UNSET(ast);
	env = env_init(envp);
	while (true)
	{
		cmd = readline("[minishell]$ ");
		ft_gcadd_back(cmd);
		if (cmd == NULL)
		{
			ft_gc_clear();
			exit(0);
		}
		printf("%s\n", cmd);
		ft_gc_clear();
	}
	return (EXIT_SUCCESS);
}

