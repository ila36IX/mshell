#include "main.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

int ft_iswspace(char c) {
        return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' ||
        c == '\v');
}

int is_word_delim(char c)
{
	return (c == '"' || c == '\'' || c == '>' || c == '<' || ft_iswspace(c) || c == '\0');
}

bool lexer_trim_left(t_lexer *l)
{
	bool	whitespace_found;

	whitespace_found = false;
	while (l->cursor < l->content_len && ft_iswspace(l->content[l->cursor]))
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

void log_error(char *msg)
{
	printf("msh: %s\n", msg);
}

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

t_token lexer_next_token(t_lexer *l)
{
	t_token token;

	ft_bzero(&token, sizeof(token));
	token.whitespace_before = lexer_trim_left(l);
	if (l->cursor >= l->content_len)
		return (token);
	else if (lexer_starts_with(l, ">>"))
	{
		token.kind = TOKEN_APPEND;
		token.text = &l->content[l->cursor];
		token.text_len = 2;
		l->cursor += 2;
	}
	else if (lexer_starts_with(l, "<<"))
	{
		token.kind = TOKEN_HEREDOC;
		token.text = &l->content[l->cursor];
		token.text_len = 2;
		l->cursor += 2;
	}
	else if (lexer_starts_with(l, "&&"))
	{
		token.kind = TOKEN_AND;
		token.text = &l->content[l->cursor];
		token.text_len = 2;
		l->cursor += 2;
	}
	else if (lexer_starts_with(l, "||"))
	{
		token.kind = TOKEN_OR;
		token.text = &l->content[l->cursor];
		token.text_len = 2;
		l->cursor += 2;
	}
	else if (l->content[l->cursor] == '|')
	{
		token.kind = TOKEN_PIPE;
		token.text = &l->content[l->cursor];
		token.text_len = 1;
		l->cursor++;
	}
	else if (l->content[l->cursor] == '<')
	{
		token.kind = TOKEN_IN;
		token.text = &l->content[l->cursor];
		token.text_len = 1;
		l->cursor++;
	}
	else if (l->content[l->cursor] == '>')
	{
		token.kind = TOKEN_OUT;
		token.text = &l->content[l->cursor];
		token.text_len = 1;
		l->cursor++;
	}
	else if (l->content[l->cursor] == '"')
	{
		token.kind = TOKEN_DQ;
		l->cursor++;
		token.text = &l->content[l->cursor];
		while (l->content[l->cursor] != '"')
		{
			token.text_len++;
			l->cursor++;
			if (!l->content[l->cursor])
			{
				token.kind = TOKEN_INVALID;
				log_error("Enclosing \"");
				return (token);
			}
		}
		l->cursor++;
	}
	else if (l->content[l->cursor] == '\'')
	{
		token.kind = TOKEN_SQ;
		l->cursor++;
		token.text = &l->content[l->cursor];
		while (l->content[l->cursor] != '\'')
		{
			token.text_len++;
			l->cursor++;
			if (!l->content[l->cursor])
			{
				token.kind = TOKEN_INVALID;
				log_error("Enclosing '");
				return (token);
			}
		}
		l->cursor++;
	}
	else
	{
		token.kind = TOKEN_WORD;
		token.text = &l->content[l->cursor];
		while (!is_word_delim(l->content[l->cursor]))
		{
			token.text_len++;
			l->cursor++;
		}
	}
	return (token);
}

const char *token_kind_name(t_token_kind kind)
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

void	print_token(t_token token)
{
	printf("%.*s ("BRED"%s" RESET ", %ld)\n", (int)token.text_len, token.text, token_kind_name(token.kind), token.text_len);
}
