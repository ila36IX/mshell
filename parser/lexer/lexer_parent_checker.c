/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parent_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:26:09 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/05 16:26:11 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/*
 * lexer_check_parens - Check if parentheses is valid
 *
 * @lexer: lexer
 *
 * Return: true if valid, false if not, lexer is not mutated
 */
bool	lexer_check_parens(t_lexer *lexer)
{
	t_token	token;
	int		depth;
	size_t	cursor_loc;

	cursor_loc = lexer->cursor;
	token = lexer_next_token(lexer);
	depth = 0;
	while (token.kind)
	{
		if (token.kind == TOKEN_OPAREN)
			depth++;
		else if (token.kind == TOKEN_CPAREN)
			depth--;
		token = lexer_next_token(lexer);
	}
	lexer->cursor = cursor_loc;
	if (depth != 0)
		return (false);
	return (true);
}
