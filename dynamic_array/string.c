/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:42:40 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/03 17:42:50 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

static int	string_ensure_capacity(t_string *s, size_t add_size)
{
	size_t	required_capacity;
	size_t	new_capacity;
	char	*new_buff;

	required_capacity = s->length + add_size + 1;
	if (s->capacity >= required_capacity)
		return (0);
	new_capacity = s->capacity * 2;
	if (new_capacity < required_capacity)
		new_capacity = required_capacity;
	new_buff = malloc(new_capacity * sizeof(char));
	if (!new_buff)
		return (-1);
	ft_memcpy(new_buff, s->buff, s->length);
	new_buff[s->length] = '\0';
	free(s->buff);
	s->buff = new_buff;
	s->capacity = new_capacity;
	return (0);
}

void	string_append_char(t_string *s, char c)
{
	string_ensure_capacity(s, 1);
	s->buff[s->length++] = c;
	s->buff[s->length] = '\0';
}

void	string_append_str(t_string *s, const char *str_to_append, size_t size)
{
	if (!str_to_append)
		return ;
	string_ensure_capacity(s, size);
	ft_memcpy(s->buff + s->length, str_to_append, size);
	s->length += size;
	s->buff[s->length] = '\0';
}

t_string	string_init(void)
{
	t_string	s;

	s.length = 0;
	s.capacity = INIT_STR_ARRAY_SIZE;
	s.buff = malloc(s.capacity * sizeof(char));
	if (s.buff)
		s.buff[0] = '\0';
	return (s);
}

void	string_append_cstr(t_string *s, const char *str_to_append)
{
	size_t	size;

	if (!str_to_append)
		return ;
	size = ft_strlen(str_to_append);
	string_ensure_capacity(s, size);
	ft_memcpy(s->buff + s->length, str_to_append, size);
	s->length += size;
	s->buff[s->length] = '\0';
}
