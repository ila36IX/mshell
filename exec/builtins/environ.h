#ifndef ENVIRON_H
# define ENVIRON_H

# include "../../main.h"

typedef enum e_env_action
{
	ENV_ACTION_GET,
	ENV_ACTION_SET,
	ENV_ACTION_UNSET,
	ENV_ACTION_FREE,
	ENV_ACTION_PRINT,
}					t_env_action;

typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}					t_dict;

void	environ_init(const char **envp);
char				*environ_get(const char *key);
void				environ_unset(const char *key);
void				environ_set(const char *key, const char *value);
void				environ_free(void);
void				environ_print(void);
char	**environ_array_execve(void);

#endif
