#include "lexer.h"
#include "parser.h"
#include "string.h"

/**
 * lexer_peek_next_token - Get the next token without moving the cursor
 *
 * @lexer: pointer to the lexer
 * Return: next token
 */
t_token lexer_peek_next_token(t_lexer *lexer)
{
	t_token token;
	size_t	cursor_location;

	cursor_location = lexer->cursor;
	token = lexer_next_token(lexer);
	lexer->cursor = cursor_location;
	return (token);
}

/**
 * lexer_next_zip_word - join expanded tokens until white space or operator
 * found into the str
 *
 * @lexer: lexer
 *
 * Return: Allocated string containing the expanded text of the token, Or NULL
 * if expanded string is empty
 */
char *lexer_next_zip_word(t_lexer *lexer)
{
	t_token token;
	t_string str;
	bool is_quoted;

	str = string_init();
	is_quoted = false;
	while (1)
	{
		token = lexer_next_token(lexer);
		token_to_expand_str(&str, token);
		if (token.kind != TOKEN_WORD)
			is_quoted = true;
		if (next_token_is_joinable(lexer) == false)
			break ;
	}
	if (!is_quoted && ft_strlen(str.buff) == 0)
	{
		free(str.buff);
		str.buff = NULL;
	}
	return (str.buff);
}
