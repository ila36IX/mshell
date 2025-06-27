#include "lexer.h"

bool	lexer_trim_left(t_lexer *l);
void	extract_word_token(t_lexer *l, t_token *token);

/**
 * lexer_starts_with - Checks if the lexer's current input starts with a
 * specific string
 *
 * @l: lexer
 * @prefix: String to be checked
 *
 * Return: true if it start with and false if not
 */
bool	lexer_starts_with(t_lexer *l, const char *prefix)
{
	size_t	i;

	i = 0;
	while (prefix[i])
	{
		if ((l->cursor + i) >= l->content_len)
			return (false);
		if (l->content[l->cursor + i] != prefix[i])
			return (false);
		i++;
	}
	return (true);
}

/**
 * is_op_token - Checks if the lexer's current input starts with a specific
 * special token string
 *
 *
 * @l: pointer to the t_lexer struct, which holds the input string
 * and current parsing position
 * @token: pointer to the t_token struct that will be filled with token
 * information if the special string is matched
 * @op: string representing the special character to check for (e.g., ">>", "|")
 * @kind: to be assign to the token if the special `op` is matched
 *
 * Return: `true` if specified `op` is found at the current lexer
 * position, `false` if no match found
 */
bool	is_special_token(t_lexer *l, t_token *token, const char *op,
		t_token_kind kind)
{
	if (lexer_starts_with(l, op))
	{
		token->kind = kind;
		token->text = &l->content[l->cursor];
		token->text_len = ft_strlen(op);
		l->cursor += ft_strlen(op);
		return (true);
	}
	return (false);
}

/**
 * check_special_tokens - check if the next token is special
 *
 * @l: A pointer to the lexer, which holds the input string and current parsing
 * position
 * @token: reference to token to be changed
 *
 * Return: true if the founded token is a special token false if no operator
 * found
 */
bool	check_special_tokens(t_lexer *l, t_token *token)
{
	if (is_special_token(l, token, ">>", TOKEN_APPEND))
		return (true);
	if (is_special_token(l, token, "<<", TOKEN_HEREDOC))
		return (true);
	if (is_special_token(l, token, "&&", TOKEN_AND))
		return (true);
	if (is_special_token(l, token, "&", TOKEN_WORD))
		return (true);
	if (is_special_token(l, token, "||", TOKEN_OR))
		return (true);
	if (is_special_token(l, token, "|", TOKEN_PIPE))
		return (true);
	if (is_special_token(l, token, "<", TOKEN_IN))
		return (true);
	if (is_special_token(l, token, ">", TOKEN_OUT))
		return (true);
	if (is_special_token(l, token, "(", TOKEN_OPAREN))
		return (true);
	if (is_special_token(l, token, ")", TOKEN_CPAREN))
		return (true);
	return (false);
}

/**
 * is_quote_token - Handler for the case of qoute token
 *
 * @l: lexer
 * @token, reference to token to be changed
 * @quote: " or '
 * @kind: TOKEN_DQ or TOKEN_SQ
 *
 * Return: true if quote token is handled.
 * false if inclosing quote is found, the text field of @token will hold the
 * error msg and the kind of the token is TOKEN_INVALID
 */
bool	is_quote_token(t_lexer *l, t_token *token, char quote,
		t_token_kind kind)
{
	if (l->content[l->cursor] != quote)
		return (false);
	token->kind = kind;
	l->cursor++;
	token->text = &l->content[l->cursor];
	while (l->content[l->cursor] != quote)
	{
		token->text_len++;
		l->cursor++;
		if (!l->content[l->cursor])
		{
			token->kind = TOKEN_INVALID;
			token->text = "Enclosing \" or '";
			token->text_len = strlen("Enclosing \" or '");
			return (true);
		}
	}
	l->cursor++;
	return (true);
}

/**
 * lexer_next_token - get next token in command
 *
 * @l: the lexer holding metadate of the traversed partion of the prompt
 *
 * Return: token type, if the token kind is invalid the token text will
 * represent the error
 */
t_token	lexer_next_token(t_lexer *l)
{
	t_token	token;

	ft_bzero(&token, sizeof(token));
	token.whitespace_before = lexer_trim_left(l);
	if (l->cursor >= l->content_len)
		return (token);
	if (check_special_tokens(l, &token))
		return (token);
	if (is_quote_token(l, &token, '"', TOKEN_DQ))
		return (token);
	if (is_quote_token(l, &token, '\'', TOKEN_SQ))
		return (token);
	extract_word_token(l, &token);
	return (token);
}
