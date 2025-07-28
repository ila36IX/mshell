#include "./libft.h"
#include <stdarg.h>

static int	print_format(const char *buffer, va_list args_list, int fd)
{
	int		idx;
	char	*str;
	int		number;

	idx = 0;
	if (buffer == NULL)
		return (ERR_NULL);
	if (buffer[idx] == 's')
	{
		str = va_arg(args_list, char *);
		if (str == NULL)
			return (FAIL);
		write(fd, str, ft_strlen(str));
		return (idx + 1);
	}
	else if (buffer[idx] == 'd')
	{
		number = va_arg(args_list, int);
		ft_putnbr_fd(number, fd);
		return (idx + 1);
	}
	else
		write(fd, buffer + idx, 1);
	return (idx + 1);
}

int	ft_dprintf(int fd, const char *buffer, ...)
{
	int		len;
	int		idx;
	va_list	args_list;

	if (buffer == NULL)
		return (FAIL);
	va_start(args_list, buffer);
	idx = 0;
	len = 0;
	while (buffer[idx])
	{
		if (buffer[idx] == '%')
			idx += print_format(buffer + idx + 1, args_list, fd);
		else
			write(fd, buffer + idx, 1);
		if (buffer[idx])
			idx += 1;
	}
	va_end(args_list);
	return (len);
}
