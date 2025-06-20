#include "lexer.h"

/*
 * lexer_check_parens - Check if parentheses is valid
 *
 * @lexer: lexer
 *
 * Return: true if valid, false if not, lexer is not mutated
 */
bool	lexer_check_parens(t_lexer *lexer)
{
	t_token	token;
	int		depth;
	size_t	cursor_loc;

	cursor_loc = lexer->cursor;
	token = lexer_next_token(lexer);
	depth = 0;
	while (token.kind)
	{
		if (token.kind == TOKEN_OPAREN)
			depth++;
		else if (token.kind == TOKEN_CPAREN)
			depth--;
		token = lexer_next_token(lexer);
	}
	lexer->cursor = cursor_loc;
	if (depth != 0)
		return (false);
	return (true);
}
