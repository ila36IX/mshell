# include "./exec.h"
# include "./builtins/environ.h"
# include "./builtins/builtins.h"
# include "./status.h"
# include "../includes.h"

# define BUILTIN 0
# define PRECOMPILED 1
# define ERR_OPEN -1
# define ERR_NULL 1



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
	// else if (access(name, F_OK | X_OK) == 0)
	// 	return (PRECOMPILED);
	return (PRECOMPILED);
}

/**
 * exec_simple_cmd - Executes a simple command with
 * arguments and redirections
 * @cmd: Command to execute with its meta-data
 * @redir: Redirection information (files, and streams)
 */
static int	exec_simple_cmd(t_ast *ast, int pipe_in)
{
	t_simple_cmd	cmd;
	int	redirect;
	int			saved_stdin;
	int			saved_stdout;
	int			pipefd[2];
	int			pipe_out;

	if (!ast)
		return (SUCCESS);
	cmd = ast->simple_cmd;
	/* Saving stding and stdout streams */
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	pipe_out = -1;
	if (ast->next && ast->next->type == AST_CONNECTOR
			&& ast->next->connector == CONNECTOR_PIPE)
	{
		pipe(pipefd);
		dup2(pipefd[1], STDOUT_FILENO);
		pipe_out = pipefd[0];
		close(pipefd[1]);
	}
	if (pipe_in != FAIL)
		dup2(pipe_in, STDIN_FILENO);
	if (saved_stdin == ERR_OPEN || saved_stdout == ERR_OPEN)
		return (ERR_OPEN);
	redirect = setup_redirect(ast);
	if (redirect == FAIL)
		return (FAIL);
	if (check_command_type(cmd.argv[0]) == BUILTIN)
		exec_builtin(ast);
	else if (check_command_type(cmd.argv[0]) == PRECOMPILED)
		exec_precompiled(ast);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	close(pipe_in);
	return (pipe_out);
}



static int exec_connected(t_ast *ast)
{
	if (!ast)
		return (FAIL);
	if (ast->connector == CONNECTOR_OR)
	{
		if (status_get() == 0)
			return (SUCCESS);
		else
			exec_simple_cmd(ast->next, -1);
	}
	if (ast->connector == CONNECTOR_AND)
	{
		if (status_get() != 0)
			return (FAIL);
		else
			exec_simple_cmd(ast->next, -1);
	}
	return (SUCCESS);
}

/**
 	* exec_main - main execution function that takes the ast
	* @ast: Ast data
 */
void	exec_main(t_ast *ast, char **envp)
{
	int	pipe_in;

	if (!ast || !envp)
		return ;
	pipe_in  = -1;
	environ_init((const char **)envp);
	while (ast)
	{
		if (ast->type == AST_SIMPLE_COMMAND)
			pipe_in = exec_simple_cmd(ast, pipe_in);
		else if (ast->type == AST_CONNECTOR)
		{
			exec_connected(ast);
			if (ast->connector != CONNECTOR_PIPE)
				ast = ast->next;
		}
		/* else if (ast->type == AST_SUBSHELL)
			exec_subshell(ast->subshell, pipe_in); */
		ast = ast->next;
	}
}

