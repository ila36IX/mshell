/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 12:08:40 by sboukiou          #+#    #+#             */
/*   Updated: 2025/07/24 12:08:41 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_H
# define ENVIRON_H

# include "../../includes.h"
# include "../../libft/libft.h"

# define ENV_SIZE 1024

/**
 * s_dict - key value
 * holding struct
 * @key: env variable key
 * @value: its value
 * next: Next env variable
 */
typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
}					t_dict;

void		environ_init(const char **envp);
const char	*environ_get(const char *key);
int			environ_unset(const char *key);
void		environ_set(const char *key, const char *value);
void		environ_free(void);
int			environ_print(void);
char		**environ_array_execve(void);
t_dict		*environ_get_head(void);
t_dict		**get_static_env_head(void);

#endif
