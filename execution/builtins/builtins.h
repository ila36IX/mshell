# ifndef BUILTINS_H
# define BUILTINS_H

# include "../../includes.h"
# include "../../types.h"
# include "../../libft/libft.h"

typedef enum e_builtin_type
{
	ECHO,
	CD,
	EXIT,
	UNSET,
	PWD,
	EXPORT,
	ENV,
	INVALID
}	t_builtin_type;

size_t	echo(const char *text, bool newline);

#endif
