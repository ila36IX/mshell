#include "./main.h"

t_token	*get_next_token(t_lexer *lexer, int argc)
{
	t_token	*token;
	(void)lexer;
	(void)argc;
	return (token);
}

static bool	is_token_redirect(t_token *token)
{
	if (token->kind == TOKEN_IN)
		return (true);
	if (token->kind == TOKEN_OUT)
		return (true);
	if (token->kind == TOKEN_HEREDOC)
		return (true);
	if (token->kind == TOKEN_APPEND)
		return (true);
	return (false);
}

t_cmd	*constrcut_cmd(t_lexer *lexer, t_cmd *cmd)
{
	t_token	*token;

	if (!lexer)
	{
		UNREACHABLE("Lexer NULL !\n");
		return (NULL);
	}
	cmd->argc = 0;
	while ((token = get_next_token(lexer, cmd->argc)) != NULL)
	{
		if (is_token_redirect(token))
			push_back_redirection(token, cmd);
		else if ()
	}
	return (cmd);
}
