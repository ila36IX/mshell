#include "lexer.h"
#include "libft/libft.h"

char *alloc_token_str(t_token token)
{
	/* NOTE: Expand will happen here */
	return (ft_substr(token.text, 0, token.text_len));
}
