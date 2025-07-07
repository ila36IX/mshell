/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:26:21 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/05 16:27:51 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * lexer_new - constactor of lexer
 *
 * @content: String that will be tokenized, it is not ended by null-char, use
 * `content_len` to traverse
 * @size: size of the string
 *
 * Return: new lexer
 */
t_lexer	lexer_new(const char *content, size_t size)
{
	t_lexer	l;

	l.content = content;
	l.content_len = size;
	l.cursor = 0;
	return (l);
}

/**
 * is_whitespace - checks if characher is a whitespace
 *
 * @c: characher to be chacked
 *
 * Return: true if its a whitespace, and false otherwise
 */
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

/**
 * is_word_delim - checks if characher is a valid word delimiter
 *
 * @c: characher to be chacked
 *
 * Return: true if its a delimiter, qnd false otherwise
 */
int	is_word_delim(char c)
{
	return (c == '>' || c == '<' || is_whitespace(c) || c == '\0' || c == '|'
		|| c == '(' || c == ')' || c == '&');
}

/**
 * is_quote_token - Handler for the case of qoute token
 *
 * @l: lexer
 * @token, reference to token to be changed
 * @quote: " or '
 * @kind: TOKEN_DQ or TOKEN_SQ
 *
 * Return: true if quote token is handled.
 * false if inclosing quote is found, the text field of @token will hold the
 * error msg and the kind of the token is TOKEN_INVALID
 */
bool	word_read_quote(t_lexer *l, t_token *token, char quote)
{
	if (l->content[l->cursor] != quote)
		return (false);
	l->cursor++;
	token->text_len++;
	while (l->content[l->cursor] != quote)
	{
		if (!l->content[l->cursor] || l->cursor >= l->content_len)
		{
			token->kind = TOKEN_INVALID;
			token->text = "Enclosing \" or '";
			token->text_len = ft_strlen("Enclosing \" or '");
			return (false);
		}
		token->text_len++;
		l->cursor++;
	}
	l->cursor++;
	token->text_len++;
	return (true);
}

/**
 * extract_word_token - extract word and put it in the token argument
 * - a word is string which surrounded by special charachter or waitspace or
 * start/end of string
 *
 * @l: lexer
 * @token: reference to token that will be filled
 * Return: Nothing
 */
void	extract_word_token(t_lexer *l, t_token *token)
{
	token->text = &l->content[l->cursor];
	token->kind = TOKEN_WORD;
	token->text_len = 0;
	while (!is_word_delim(l->content[l->cursor]) && l->cursor < l->content_len)
	{
		if (l->content[l->cursor] == '"' || l->content[l->cursor] == '\'')
		{
			word_read_quote(l, token, l->content[l->cursor]);
		}
		else
		{
			token->text_len++;
			l->cursor++;
		}
		if (l->content[l->cursor] == '&' && l->content[l->cursor + 1] != '&')
		{
			token->text_len++;
			l->cursor++;
		}
	}
}
