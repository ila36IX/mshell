#include "lexer.h"
#include "string.h"
#include "environ.h"

char *environ_get_ncstr(const char *s, size_t size)
{
	t_string string;
	char *value;

	value = NULL;
	string = string_init();
	string_append_str(&string, s, size);
	value =	envron_get(string.buff);
	printf("GET: %s => %s\n", string.buff, value);
	free(string.buff);
	return (value);
}

size_t handle_expand(t_string *str, const char *s, size_t curr_idx, size_t size)
{
	size_t i;
	const char *s_pos;
	char *value;

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

char *expand_tok(const char *s, size_t size)
{
	t_string str;
	size_t i;
	
	i = 0;
	str = string_init();
	while (i < size)
	{
		if (s[i] == '$' && (ft_isalpha(s[i + 1]) || s[i + 1] == '_'))
		{
			i++;
			i += (handle_expand(&str, s, i, size));
		}
		else
			string_append_char(&str, s[i++]);
	}
	return (str.buff);
}

char *alloc_token_str(t_token token)
{
	return (expand_tok(token.text, token.text_len));
}
