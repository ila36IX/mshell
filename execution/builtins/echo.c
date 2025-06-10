# include "./builtins.h"


/**
	* echo - Mimics the behavior of the echo command
	* writes the given arguemnt/text to STDOUT
	* @text: Text to write out
	* @:newline Option of adding a newline afterwards
	* Return: Number of bytes written or EXIT_FAILURE (1) instead
*/

int	echo(const char *text, bool newline)
{
	int	written;
	int	text_len;

	if (text == NULL)
		return (EXIT_FAILURE);
	text_len = ft_strlen(text);
	if (newline == true)
		written = printf("%s\n", text);
	else
		written = printf("%s", text);
	if (text_len > written)
		return (EXIT_FAILURE);
	return (written);
}
