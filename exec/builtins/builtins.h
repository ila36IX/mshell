#ifndef BUILTINS_H
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
int		ft_echo(int ac, char **av);
int		ft_cd(int ac, char **av);
int		ft_pwd(int ac, char **av);
int		ft_export(int ac, char **av);
int		ft_unset(int ac, char **av);
int		ft_env(int ac, char **av);
int		ft_exit(int ac, char **av);
/* Env utils-funcs */

#endif
