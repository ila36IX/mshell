#include "../../includes.h"
# include "./environ.h"


int	ft_pwd(void)
{
	char		current_working_dir[MAX_WD_SIZE];
	const char	*current_dir_env;
	int		status;

	status = EXIT_SUCCESS;
	current_dir_env = environ_get("PWD");
	if (current_dir_env)
	{
		printf("%s\n", current_dir_env);
		return (status);
	}
	else if (getcwd(current_working_dir, MAX_WD_SIZE) == SUCCESS)
	{
		printf("%s\n", current_working_dir);
		return (status);
	}
	status = EXIT_FAILURE;
	return (status);
}
