# include "./exec.h"
# include "./builtins/environ.h"
# include "./builtins/builtins.h"
# include "./status.h"
# include "../includes.h"

# define BUILTIN 0
# define PRECOMPILED 1
# define ERR_OPEN -1
# define ERR_NULL 1
# define WAIT_ALL_CHILDREN -1
# define PIPE_SIZE 255



/**
 * check_command_type - Checks for the type of given command by name
 * @name: A string given as comman name (EX: ls)
 * Return: Type of the given command or NOT_FOUND for invalid names
 */
int	check_command_type(char *name)
{

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
	return (PRECOMPILED);
}

/**
 * exec_simple_cmd - Executes a simple command with
 * arguments and redirections
 * @cmd: Command to execute with its meta-data
 * @redir: Redirection information (files, and streams)
 */
int	exec_simple_cmd(t_ast *ast, int pipes[255][2], int pipe_count, int command_count)
{
	t_simple_cmd	cmd;

	if (!ast)
		return (FAIL);
	cmd = ast->simple_cmd;
	if (command_count == 0)
	{
		if (pipe_next(ast) == true)
			setup_fds(ast, -1, pipes[command_count][1]);
		else
			setup_fds(ast, -1, -1);
	}
	else if (pipe_next(ast) == false)
		setup_fds(ast, pipes[command_count - 1][0], -1);
	else
		setup_fds(ast, pipes[command_count - 1][0], pipes[command_count][1]);
	for (int i = 0; i < pipe_count; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	if (check_command_type(cmd.argv[0]) == BUILTIN)
		exec_builtin(ast);
	else if (check_command_type(cmd.argv[0]) == PRECOMPILED)
		exec_precompiled(ast);
	exit(status_get());
	return (SUCCESS);
}


/**
 	* exec_main - main execution function that takes the ast
	* @ast: Ast data
 */
int	exec_main(t_ast *ast, char **envp)
{
	pid_t	subshell;

	environ_init((const char **)(envp));
	while (ast)
	{
		if (ast->type == AST_SIMPLE_COMMAND)
		{
			execute_simple_command(ast);
			while (ast)
			{
				if (ast->type == AST_CONNECTOR && ast->connector != CONNECTOR_PIPE)
					break;
				ast = ast->next;
			}
		}
		else if (ast->type == AST_CONNECTOR && status_get() == 0 && ast->connector == CONNECTOR_AND)
			ast = ast->next;
		else if (ast->type == AST_CONNECTOR && status_get() != 0 && ast->connector == CONNECTOR_AND)
			ast = ast->next->next;
		else if (ast->type == AST_CONNECTOR && status_get() != 0 && ast->connector == CONNECTOR_OR)
			ast = ast->next;
		else if (ast->type == AST_CONNECTOR && status_get() == 0 && ast->connector == CONNECTOR_OR)
			ast = ast->next->next;
	}
	while (waitpid(WAIT_ALL_CHILDREN, NULL , 0) > 0);
	return (SUCCESS);
}
