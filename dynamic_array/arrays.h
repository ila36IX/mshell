/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:42:16 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/03 17:42:18 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAYS_H
# define ARRAYS_H

# include "../includes.h"

typedef struct s_word
{
	const char	*text;
	size_t		len;
}				t_word;

typedef struct s_words
{
	t_word		*buff;
	size_t		capacity;
	size_t		length;
}				t_words;
void			words_append(t_words *words, t_word word);
t_words			words_init(void);

#endif
