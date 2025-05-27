# include "../main.h"

/* TODO: Implement this*/
bool	is_builtin(char *command)
{
	return (false);
}

/* TODO: Implement this*/
bool	is_executable(char *command)
{
	return (false);
}

/* TODO: Implement this*/
int	execute_simple_builtin(int ac, char **av)
{
	int	status;
	return (status);
}

/* TODO: Implement this*/
int	execute_simple_precompiled(int ac, char **av)
{
	int	status;
	return (status);
}

/**
	* exec-simple_cmd - Runs a simple command
	* @cmd: Structure holding command name and its arguments & their count
	* @Return: The return status of the cmd or EXIT_FAILURE otherwise
*/
int	exec_simple_command(t_simple_cmd *cmd)
{
	int	status;

	if (!cmd)
		return (EXIT_FAILURE);
	if (cmd->argv == NULL || cmd->argc == 0)
		return (EXIT_FAILURE);
	if (is_builtin(cmd->argv[0]) == true)
		status = execute_simple_builtin(cmd->argc, cmd->argv);
	else if (is_executable(cmd->argv[0]) == true)
		status = execute_simple_precompiled(cmd->argc, cmd->argv);
	else
	{
		perror("Command not found\n");
		status = EXIT_FAILURE;
	}
	return (status);
	return (status);
}
