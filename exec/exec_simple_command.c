# include "../includes.h"
# include "./exec.h"
# include "../libft/libft.h"
# include "./builtins/builtins.h"

# define PIPE_SIZE 255
# define WAIT_ALL_CHILDREN -1

int	execute_simple_command(t_ast *ast)
{
	int		pipes[PIPE_SIZE][2];
	int		pipe_count;
	int		command_count;
	pid_t	pid;

	if (ast == NULL)
		return (FAIL);
	pipe_count = 0;
	command_count = 0;
	pipe_count = 0;
	command_count = 0;
	while (ast)
	{
		if (ast->type == AST_SIMPLE_COMMAND)
		{
			if (ft_strcmp(ast->simple_cmd.argv[0], "exit") == 0)
				quit(ast->simple_cmd.argv, ast->simple_cmd.argc);
			if (pipe_next(ast) == true)
			{
				pipe(pipes[pipe_count]);
				pipe_count += 1;
			}
			pid = fork();
			if (pid == 0)
				exec_simple_cmd(ast, pipes, pipe_count, command_count);
			command_count += 1;
		}
		else if (ast->type == AST_CONNECTOR)
		{
			if (ast->connector != CONNECTOR_PIPE)
				break;
		}
		ast = ast->next;
	}
	for (int i = 0; i < pipe_count; i++)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	while (waitpid(WAIT_ALL_CHILDREN, NULL , 0) > 0);

	return (SUCCESS);
}
