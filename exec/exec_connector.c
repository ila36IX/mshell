# include "./exec.h"
# include "./status.h"

int exec_connector(t_ast *ast)
{
	if (!ast)
		return (FAIL);
	if (ast->connector == CONNECTOR_OR)
	{
		if (status_get() == 0)
			return (SUCCESS);
	}
	else if (ast->connector == CONNECTOR_AND)
	{
		if (status_get() != 0)
			return (FAIL);
	}
	return (SUCCESS);
}
