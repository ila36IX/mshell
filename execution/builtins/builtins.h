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
int	env(char **envp);

#endif
