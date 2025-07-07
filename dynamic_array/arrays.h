/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:42:16 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/05 16:48:45 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAYS_H
# define ARRAYS_H
# include "../includes.h"
# include "../types.h"

void			words_append(t_words *words, t_word word);
t_words			words_init(void);
void	args_append(t_simple_cmd *scmd, char *arg);
void	init_argv(t_simple_cmd *scmd);

#endif
