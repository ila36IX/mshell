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

char	*get_full_pathname(char *name)
{
	char	**list;
	const char	*env;
	char	*final_path;
	int	i;

	if (!name)
		return (NULL);
	if (access(name, F_OK | X_OK) == 0)
		return (name);
	env = environ_get("PATH");
	if (!env)
		return (NULL);
	list = ft_split(env, ':');
	if (!list)
		return (NULL);
	i = 0;
	while (list[i])
	{
		final_path = ft_strjoin(list[i], "/");
		final_path = ft_strjoin(final_path, name);
		if (access(final_path, F_OK | X_OK) == 0)
			return (final_path);
		ft_gc_remove(final_path);
		i++;
	}
	ft_gc_remove_ft_split(list);
	return (NULL);
}

/**
 * Executes an executble-file command
 * @ast: Ast structure
 * Return: Exit status of the given command
 */
int	exec_precompiled(t_ast *ast)
{
	pid_t	pid;
	char	**envp;
	char	*cmd;
	int		status;

	if (!ast)
		return (EXIT_FAILURE);
	cmd = get_full_pathname(ast->simple_cmd.argv[0]);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	status = 0;
	if (pid == 0)
	{
		if (cmd == NULL)
		{
			dprintf(STDERR_FILENO, "%s: command not found\n", ast->simple_cmd.argv[0]);
			exit(NOT_FOUND);
		}
		envp = environ_array_execve();
		if (execve(cmd, ast->simple_cmd.argv, envp) == -1)
			exit(NOT_FOUND);
	}
	else
		waitpid(pid, &status, 0);
	status_set(WEXITSTATUS(status));
	return (EXIT_SUCCESS);
}

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
		dprintf(saved_stdin, "Failed to setup the redirections\n");
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
		/*else if (ast->type == AST_SUBSHELL)*/
		/*		return (main_exec(ast->subshell, env));*/
		/*else if (ast->type == CONNECTOR)*/
		/*		return (main_exec(ast->connector, env));*/
		ast = ast->next;
	}
}
