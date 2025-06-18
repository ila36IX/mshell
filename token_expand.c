#include "lexer.h"
#include "string.h"
#include "./exec/builtins/environ.h"

/**
 * environ_get_ncstr - get environment varaible of string using its size
 *
 * @s: string identifies by its size, not by null terminator at the end
 * @size: size of s
 *
 * Return: Pointer of string from the environ varaible
 */
const char *environ_get_ncstr(const char *s, size_t size)
{
	t_string string;
	const char *value;

	value = NULL;
	string = string_init();
	string_append_str(&string, s, size);
	value =	environ_get(string.buff);
	printf("GET: %s => %s\n", string.buff, value);
	free(string.buff);
	return (value);
}

size_t handle_expand(t_string *str, const char *s, size_t curr_idx, size_t size)
{
	size_t i;
	const char *s_pos;
	const char *value;

	s_pos = &s[curr_idx];
	i = 0;
	while (curr_idx < size && (ft_isalnum(s[curr_idx]) || s[curr_idx] == '_'))
	{
		i++;
		curr_idx++;
	}
	if (i == 0)
		return (0);
	value = environ_get_ncstr(s_pos, i);
	string_append_cstr(str, value);
	return (i);
}

void expand_tok(t_string *str, const char *s, size_t size)
{
	size_t i;
	
	i = 0;
	while (i < size)
	{
		if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '_'))
		{
			i++;
			i += (handle_expand(str, s, i, size));
		}
		else
			string_append_char(str, s[i++]);
	}
}

char *alloc_token_str(t_token token)
{
	return (ft_substr(token.text, 0, token.text_len));
}

/**
 * token_to_expand_str - Join the text of the token after expanding to the
 * content of str variable
 *
 * @str: dynamic array of charachters
 * @token: the token to be added into str
 *
 * Return: Nothing, token text will be expanded then appended into the str
 */
void token_to_expand_str(t_string *str, t_token token)
{
	if (token.kind == TOKEN_SQ)
		string_append_str(str, token.text, token.text_len);
	else
		expand_tok(str, token.text, token.text_len);
}
