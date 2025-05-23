#include "main.h"

int ft_isspace(char c) {
        return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
        c == '\v');
}

bool lexer_trim_left(t_lexer *l)
{
	bool	whitespace_found;

	whitespace_found = false;
	while (l->cursor < l->content_len && ft_isspace(l->content[l->cursor]))
	{
		l->cursor++;
		whitespace_found = true;
	}
	return (whitespace_found);
}

t_lexer lexer_new(const char *content, size_t size)
{
	t_lexer l;

	l.content = content;
	l.content_len = size;
	l.cursor = 0;
	return (l);
}


t_token lexer_next_token(t_lexer *l)
{
	t_token token;

	ft_bzero(&token, sizeof(token));
	token.whitespace_before = lexer_trim_left(l);
	if (l->cursor >= l->content_len)
		return (token);
	else if (l->content[l->cursor] == '|')
	{
		token.kind = TOKEN_PIPE;
		token.text = &l->content[l->cursor];
		token.text_len = 1;
		l->cursor++;
	}
	else
	{
		token.kind = TOKEN_INVALID;
		token.text = &l->content[l->cursor];
		token.text_len = 1;
		l->cursor++;
	}
	return (token);
}

const char *token_kind_name(t_token_kind kind)
{
	if (kind == TOKEN_INVALID)
		return ("invalid token");
	else if (kind == TOKEN_PIPE)
		return ("token pipe");
	UNREACHABLE("All the cases must have its case handled");
}

void	print_token(t_token token)
{
	printf("%.*s (%s)\n", (int)token.text_len, token.text, token_kind_name(token.kind));
}
