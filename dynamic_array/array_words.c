/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:42:23 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/03 17:42:53 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "arrays.h"

#define INIT_WORDS_ARRAY_SIZE 16

static int	words_ensure_capacity(t_words *words)
{
	size_t	required_capacity;
	size_t	new_capacity;
	t_word	*new_buff;

	required_capacity = words->length + 1;
	if (words->capacity >= required_capacity)
		return (0);
	new_capacity = words->capacity * 2;
	new_buff = ft_malloc(new_capacity, sizeof(t_word));
	if (!new_buff)
		return (-1);
	ft_memcpy(new_buff, words->buff, words->length * sizeof(t_word));
	words->buff = new_buff;
	words->capacity = new_capacity;
	return (0);
}

void	words_append(t_words *words, t_word word)
{
	words_ensure_capacity(words);
	words->buff[words->length++] = word;
}

t_words	words_init(void)
{
	t_words	words;

	words.length = 0;
	words.capacity = INIT_WORDS_ARRAY_SIZE;
	words.buff = ft_malloc(words.capacity, sizeof(t_word));
	return (words);
}
