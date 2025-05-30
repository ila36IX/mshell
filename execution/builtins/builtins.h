# ifndef BUILTINS_H
# define BUILTINS_H

# include "../../includes.h"
# include "../../types.h"
# include "../../libft/libft.h"

typedef struct s_env_dict
{
	char	*key;
	char	*val;
}	t_env_dict;

int	echo(const char *text, bool newline);
int	pwd(void);
int	cd(int ac, char **av);
/* Env utils-funcs */
int	env(char **envp);
static void	env_insert(t_list **head, char *key, char *value);
static void	env_remove(t_list *head, char *key);

#endif
