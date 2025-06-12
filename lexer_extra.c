#include "parser.h"

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
 */
char *lexer_next_zip_word(t_lexer *lexer)
{
	char   *zip_word;
	char   *tmp_zip_word;
	t_token token;

	token = lexer_next_token(lexer);
	zip_word = alloc_token_str(token);
	while (next_token_is_joinable(lexer))
	{
		token = lexer_next_token(lexer);
		tmp_zip_word = alloc_token_str(token);
		zip_word = ft_strjoin(zip_word, tmp_zip_word);
	}
	return (zip_word);
}
