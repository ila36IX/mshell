# include "../includes.h"
#include "./builtins/environ.h"
# include "../libft/libft.h"

# define GET 0
# define SET 1


/**
 * status_main - Gets/Sets the global status value based on an action
 * @action: GET or SET
 * @status: Pointer the value to act on
 */
static void	status_main(int action, int *status)
{
	static int	s_status;

	if (action == GET)
		*status = s_status;
	else if (action == SET)
	{
		s_status = *status;
	}
}

/**
 * status_get - Gets the global last exit status
 * Return: Value of the last exit status number
 */
int	status_get(void)
{
	int	status;
	status_main(GET, &status);
	return (status);
}

/**
 * status_set - Sets the global last exit status
 * @: status: Value to set
 */
void	status_set(int status)
{
	status_main(SET, &status);

}
