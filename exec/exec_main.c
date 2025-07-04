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
static int	exec_simple_cmd(t_ast *ast, int pipe_in, int pipe_out)
{
	t_simple_cmd	cmd;
	int				redirect;

	if (!ast)
		exit(0);
	cmd = ast->simple_cmd;
	if (ast->next && ast->next->type == AST_CONNECTOR
			&& ast->next->connector == CONNECTOR_PIPE)
	{
		dup2(pipe_out, STDOUT_FILENO);
		close(pipe_out);
	}
	if (pipe_in != -1)
	{
		dup2(pipe_in, STDIN_FILENO);
		close(pipe_in);
	}
	redirect = setup_redirect(ast);
	if (redirect == FAIL)
		return (FAIL);
	if (check_command_type(cmd.argv[0]) == BUILTIN)
		exec_builtin(ast);
	else if (check_command_type(cmd.argv[0]) == PRECOMPILED)
		exec_precompiled(ast);
	exit(status_get());
	return (SUCCESS);
}



static int exec_connected(t_ast *ast, int pipe_out)
{
	if (!ast)
		return (FAIL);
	if (ast->connector == CONNECTOR_OR)
	{
		if (status_get() == 0)
			return (SUCCESS);
		else
			exec_simple_cmd(ast->next, -1, pipe_out);
	}
	else if (ast->connector == CONNECTOR_AND)
	{
		if (status_get() != 0)
			return (FAIL);
		else
			exec_simple_cmd(ast->next, -1, pipe_out);
	}
	return (SUCCESS);
}

/**
 	* exec_main - main execution function that takes the ast
	* @ast: Ast data
 */
void	exec_main(t_ast *ast, char **envp)
{
	int		pipe_in;
	int		pipe_out;
	pid_t	pid;
	int		pipefd[2];

	if (!ast || !envp)
		return ;
	pipe_in  = -1;
	pipe_out  = -1;
	pid = 0;
	status_set(0);
	environ_init((const char **)envp);
	while (ast)
	{
		if (ast->type == AST_SIMPLE_COMMAND)
		{
			if (ast->next && ast->next->type == AST_CONNECTOR
					&& ast->next->connector == CONNECTOR_PIPE)
			{
				if (pipe(pipefd) == FAIL)
					return ;
				pipe_out = pipefd[1];
			}
			if (ft_strcmp(ast->simple_cmd.argv[0], "exit") != 0)
				pid = fork();
			if (pid == FAIL)
				return ;
			if (pid == 0)
				exec_simple_cmd(ast, pipe_in, pipe_out);
			pipe_in = -1;
		}
		else if (ast->type == AST_CONNECTOR)
		{
			if (ast->connector == CONNECTOR_PIPE)
				pipe_in = pipefd[0];
			exec_connected(ast, pipe_out);
			if (ast->connector != CONNECTOR_PIPE)
				ast = ast->next;
		}
		if (pipe_out != FAIL)
			close(pipefd[1]);
		/* if (pipe_in != FAIL)
			close(pipefd[0]); */
		ast = ast->next;
	}
	if (pid > 0)
		waitpid(pid, NULL, 0);
	kill(-9, SIGKILL);
}

