/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:41:36 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/03 17:41:39 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H
# include "../libft/libft.h"
# define INIT_STR_ARRAY_SIZE 16

typedef struct s_string
{
	size_t	length;
	size_t	capacity;
	char	*buff;
}			t_string;

void		string_append_char(t_string *s, char c);
void		string_append_str(t_string *s, const char *str_to_append,
				size_t size);
t_string	string_init(void);
void		string_append_cstr(t_string *s, const char *str_to_append);

#endif
