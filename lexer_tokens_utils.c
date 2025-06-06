#include "lexer.h"
#include "main.h"

bool token_is_word(t_token token)
{
	return (token.kind == TOKEN_DQ || token.kind == TOKEN_SQ ||
		token.kind == TOKEN_WORD);
}
bool token_is_redir_op(t_token token)
{
	return (token.kind == TOKEN_OUT || token.kind == TOKEN_IN ||
		token.kind == TOKEN_HEREDOC || token.kind == TOKEN_APPEND);
}

bool token_is_operator(t_token token)
{
	return (token.kind == TOKEN_PIPE || token.kind == TOKEN_AND ||
		token.kind == TOKEN_OR);
}

bool next_token_is_joinable(t_lexer *lexer)
{
	t_token token;

	token = lexer_peek_next_token(lexer);
	if (token_is_word(token))
		return (token.whitespace_before == false);
	return (false);
}

t_redirect_type tok_kind_to_redir_type(t_token_kind kind)
{
	if (kind == TOKEN_OUT)
		return (REDIR_TYPE_OUT);
	else if (kind == TOKEN_IN)
		return (REDIR_TYPE_IN);
	else if (kind == TOKEN_APPEND)
		return (REDIR_TYPE_APPEND);
	else if (kind == TOKEN_HEREDOC)
		return (REDIR_TYPE_HEREDOC);
	else
	{
		UNREACHABLE("Undefind token kind!");
	}
}
