#include "../main.h"


size_t	echo(const char *text, bool newline)
{
	size_t	text_len;

	text_len = write(STDOUT_FILENO, text, ft_strlen(text));
	if (newline == true)
		text_len += write(STDOUT_FILENO, "\n", 1);
	return (text_len);
}
