#include "libft.h"

/*
 * xstrdup - allocate duplication of string wihtout using gc
 *
 * @src: String to be duplicated
 *
 * Return: Pointer to allocated string
 **/
char	*xgc_strdup(const char *src)
{
	char	*str;
	int		i;

	i = 0;
	while (src[i])
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (*src)
		str[i++] = *src++;
	str[i] = '\0';
	return (str);
}

