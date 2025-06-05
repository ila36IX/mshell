#include "lexer.h"

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
		|| c == '\0' || c == '|' || c == '(' || c == ')');
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
 * extract_word_token - extract word and put it in the token argument
 * - a word is string which surrounded by special charachter or waitspace or
 * start/end of string
 *
 * @l: lexer
 * @token: reference to token that will be filled
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
