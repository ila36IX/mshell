#include "./builtins.h"

# define MAX_BUFF_SIZE 1024

int	pwd(void)
{
	char	current_working_dir[MAX_BUFF_SIZE];
	int	status;

	status = EXIT_SUCCESS;
	if (getcwd(current_working_dir, MAX_BUFF_SIZE) ==  NULL)
		status = EXIT_FAILURE;
	printf("%s\n", current_working_dir);
	return (status);
}
