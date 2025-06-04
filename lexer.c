#include "main.h"

/**
 * is_whitespace - checks if characher is a whitespace
 *
 * @c: characher to be chacked
 *
 * Return: true if its a whitespace, and false otherwise
 */
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

/**
 * is_word_delim - checks if characher is a valid word delimiter
 *
 * @c: characher to be chacked
 *
 * Return: true if its a delimiter, qnd false otherwise
 */
int	is_word_delim(char c)
{
	return (c == '"' || c == '\'' || c == '>' || c == '<' || is_whitespace(c)
		|| c == '\0' || c == '|');
}

/**
 * lexer_trim_left - trim white spaces from lexer current position
 *
 * @l: lexer
 *
 * Return: true if lexer cursor moved, and false if not
 */
bool	lexer_trim_left(t_lexer *l)
{
	bool	whitespace_found;

	whitespace_found = false;
	while (l->cursor < l->content_len && is_whitespace(l->content[l->cursor]))
	{
		l->cursor++;
		whitespace_found = true;
	}
	return (whitespace_found);
}

/**
 * lexer_new - constactor of lexer
 *
 * @content: String that will be tokenized, it is not ended by null-char, use
 * `content_len` to traverse
 * @size: size of the string
 *
 * Return: new lexer
 */
t_lexer	lexer_new(const char *content, size_t size)
{
	t_lexer	l;

	l.content = content;
	l.content_len = size;
	l.cursor = 0;
	return (l);
}

void	log_error(char *msg)
{
	printf("msh: %s\n", msg);
}

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
 * operator string
 *
 *
 * @l: pointer to the t_lexer struct, which holds the input string
 * and current parsing position
 * @token: pointer to the t_token struct that will be filled with token
 * information if the operator is matched
 * @op: string representing the operator to check for (e.g., ">>", "|")
 * @kind: to be assign to the token if the operator `op` is matched.
 *
 * Return: `true` if the specified operator `op` is found at the current lexer
 * position, `false` if no match found
 */
bool	is_op_token(t_lexer *l, t_token *token, const char *op,
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
 * check_op_tokens - check if the following token is an operator
 *
 * @l: A pointer to the lexer, which holds the input string and current parsing
 * position
 * @token: reference to token to be changed
 *
 * Return: true if the founded token is a valid operator
 * false if no operator found
 */
bool	check_op_tokens(t_lexer *l, t_token *token)
{
	if (is_op_token(l, token, ">>", TOKEN_APPEND))
		return (true);
	if (is_op_token(l, token, "<<", TOKEN_HEREDOC))
		return (true);
	if (is_op_token(l, token, "&&", TOKEN_AND))
		return (true);
	if (is_op_token(l, token, "||", TOKEN_OR))
		return (true);
	if (is_op_token(l, token, "|", TOKEN_PIPE))
		return (true);
	if (is_op_token(l, token, "<", TOKEN_IN))
		return (true);
	if (is_op_token(l, token, ">", TOKEN_OUT))
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
 * extract_word_token - extract word and put it in the token argument
 * - a word is string which surrounded by special charachter or waitspace or
 * start/end of string
 *
 * @l: lexer
 * @token: reference to token that will be filled
 *
 * Return: Nothing
 */
void	extract_word_token(t_lexer *l, t_token *token)
{
	token->kind = TOKEN_WORD;
	token->text = &l->content[l->cursor];
	while (!is_word_delim(l->content[l->cursor]))
	{
		token->text_len++;
		l->cursor++;
	}
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
	if (check_op_tokens(l, &token))
		return (token);
	if (is_quote_token(l, &token, '"', TOKEN_DQ))
		return (token);
	if (is_quote_token(l, &token, '\'', TOKEN_SQ))
		return (token);
	extract_word_token(l, &token);
	return (token);
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
	else if (kind == TOKEN_DQ)
		return ("d-qoute str");
	else if (kind == TOKEN_SQ)
		return ("s-qoute str");
	else if (kind == TOKEN_AND)
		return ("and operator");
	else if (kind == TOKEN_OR)
		return ("or operator");
	UNREACHABLE("All the cases must have its case handled");
}

/**
 * print_token - print token representation and its size
 *
 * @token: Token to be printted
 * Return: Nothing
 */
void	print_token(t_token token)
{
	printf("%.*s (" TEXT_BRED "%s" TEXT_RESET ", %ld)\n", (int)token.text_len, token.text,
		token_kind_name(token.kind), token.text_len);
}
