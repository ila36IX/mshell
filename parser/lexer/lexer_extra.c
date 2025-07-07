/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:26:23 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/05 17:00:50 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * lexer_peek_next_token - Get the next token without moving the cursor
 *
 * @lexer: pointer to the lexer
 * Return: next token
 */
t_token	lexer_peek_next_token(t_lexer *lexer)
{
	t_token	token;
	size_t	cursor_location;

	cursor_location = lexer->cursor;
	token = lexer_next_token(lexer);
	lexer->cursor = cursor_location;
	return (token);
}

/**
 * lexer_trim_left - trim white spaces from lexer current position
 *
 * @l: lexer
 *
 * Return: true if lexer cursor moved, and false if not
 */
bool	lexer_trim_left(t_lexer *l)
{
	bool	whitespace_found;

	whitespace_found = false;
	while (l->cursor < l->content_len && is_whitespace(l->content[l->cursor]))
	{
		l->cursor++;
		whitespace_found = true;
	}
	return (whitespace_found);
}
