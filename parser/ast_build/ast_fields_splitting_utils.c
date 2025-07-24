/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_fields_splitting_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:46:56 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/22 17:46:56 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "./ast_parser.h"

bool	needs_field_splitting(char *word)
{
	size_t	i;

	i = 0;
	while (word && word[i])
	{
		if (word[i] == '"' || word[i] == '\'')
			skip_quotes(word, &i);
		else
		{
			if (is_whitespace(word[i]))
				return (true);
			i++;
		}
	}
	return (false);
}
