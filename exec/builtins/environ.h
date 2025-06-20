#ifndef ENVIRON_H
# define ENVIRON_H

#include <stdlib.h>
#include "../../libft/libft.h"
typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}					t_dict;

void	environ_init(const char **envp);
const char				*environ_get(const char *key);
void				environ_unset(const char *key);
void				environ_set(const char *key, const char *value);
void				environ_free(void);
void				environ_print(void);
char	**environ_array_execve(void);

#endif
