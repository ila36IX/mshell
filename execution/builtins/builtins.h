# ifndef BUILTINS_H
# define BUILTINS_H

# include "../../includes.h"
# include "../../types.h"
# include "../../libft/libft.h"

/*
 * s_env_dict - type for env dictionary
 * @key: key
 * @val: value
 */
typedef struct s_env_dict
{
	char	*key;
	char	*val;
}	t_env_dict;

/* Built-in functions */
int	echo(const char *text, bool newline);
int	pwd(void);
int	cd(int ac, char **av);
/* Env utils-funcs */
int	env(char **envp);
void	env_insert(t_list **head, char *key, char *value);
void	env_remove(t_list *head, char *key);

#endif
