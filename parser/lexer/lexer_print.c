#include "lexer.h"

static const char	*more_token_kind_name(t_token_kind kind)
{
	if (kind == TOKEN_OPAREN)
		return ("open paren");
	else if (kind == TOKEN_CPAREN)
		return ("close paren");
	else if (kind == TOKEN_NULL)
		return ("EOF");
	UNREACHABLE("All the cases must have its case handled");
}

/**
 * token_kind_name - corresponding descriptions of token kind
 *
 * @kind: Token kind
 * Return: String describing the token kind
 */
const char	*token_kind_name(t_token_kind kind)
{
	if (kind == TOKEN_INVALID)
		return ("invalid token");
	else if (kind == TOKEN_PIPE)
		return ("pipe line");
	else if (kind == TOKEN_IN)
		return ("input redirect");
	else if (kind == TOKEN_OUT)
		return ("ouptut redirect");
	else if (kind == TOKEN_APPEND)
		return ("append redirect");
	else if (kind == TOKEN_HEREDOC)
		return ("herdoc redirect");
	else if (kind == TOKEN_WORD)
		return ("word");
	else if (kind == TOKEN_AND)
		return ("and operator");
	else if (kind == TOKEN_OR)
		return ("or operator");
	return (more_token_kind_name(kind));
}

/**
 * print_token - print token representation and its size
 *
 * @token: Token to be printted
 * Return: Nothing
 */
void	print_token(t_token token)
{
	printf("%.*s (" TEXT_BRED "%s" TEXT_RESET ", %ld)\n", (int)token.text_len,
		token.text, token_kind_name(token.kind), token.text_len);
}

/**
 * print_lexer_tokens - print all tokens inside the lexer
 *
 * @lexer: lexer
 * Return: Nothing
 */
void	print_lexer_tokens(t_lexer *lexer)
{
	t_token	token;

	token = lexer_next_token(lexer);
	while (token.kind)
	{
		print_token(token);
		token = lexer_next_token(lexer);
	}
	print_token(token);
}
