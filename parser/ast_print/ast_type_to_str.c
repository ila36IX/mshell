#include "ast_print.h"

/**
 * ast_type_to_str - Get string representatoin of a ast type
 *
 * @type: ast type to be represented
 * Return: constant LATERAL string
 */
const char	*ast_type_to_str(t_ast_type type)
{
	if (type == AST_CONNECTOR)
		return ("CONNECTOR");
	else if (type == AST_SUBSHELL)
		return ("SUBSHELL");
	else if (type == AST_SIMPLE_COMMAND)
		return ("SIMPLE COMMAND");
	else
	{
		UNREACHABLE("ast type string represenation needed!");
	}
}

/**
 * connector_type_to_str - Get string representatoin of a connector type
 *
 * @type: connector type to be represented
 * Return: constant LATERAL string
 */
const char	*connector_type_to_str(t_connector type)
{
	if (type == CONNECTOR_AND)
		return ("AND");
	else if (type == CONNECTOR_OR)
		return ("OR");
	else if (type == CONNECTOR_PIPE)
		return ("PIPE");
	else
	{
		UNREACHABLE("Unknown connector type!");
	}
}

/**
 * redir_type_to_str - Get string representatoin of a redirection type
 *
 * @type: redicretion type to be represented
 * Return: constant LATERAL string
 */
const char	*redir_type_to_str(t_redirect_type type)
{
	if (type == REDIR_TYPE_IN)
		return ("<");
	else if (type == REDIR_TYPE_OUT)
		return (">");
	else if (type == REDIR_TYPE_HEREDOC)
		return (">>");
	else if (type == REDIR_TYPE_APPEND)
		return (">>");
	else
	{
		UNREACHABLE("Unknown redirect type!");
	}
}
