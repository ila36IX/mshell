/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aljbari <jbariali002@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 16:26:00 by aljbari           #+#    #+#             */
/*   Updated: 2025/07/05 16:28:58 by aljbari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "../../debug_macroc.h"
# include "../../dynamic_array/string.h"
# include "../../types.h"

typedef enum e_token_kind
{
	TOKEN_NULL = 0,
	TOKEN_IN,
	TOKEN_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_PIPE,
	TOKEN_WORD,
	TOKEN_OPAREN,
	TOKEN_CPAREN,
	TOKEN_INVALID,
}					t_token_kind;

typedef struct s_lexer
{
	const char		*content;
	size_t			content_len;
	size_t			cursor;
}					t_lexer;

/**
 * t_token - a slice of the user input that represent a valid token
 *
 * @kind: type of this token
 * @text: Pointer of the beginning of the token
 * @text_len: size of this token, do not expect null charachter in the end, this
 * is only a slice
 */
typedef struct s_token
{
	t_token_kind	kind;
	const char		*text;
	size_t			text_len;
}					t_token;

t_lexer				lexer_new(const char *content, size_t size);
t_token				lexer_next_token(t_lexer *l);
const char			*token_kind_name(t_token_kind kind);
void				print_token(t_token token);
void				print_lexer_tokens(t_lexer *lexer);
char				*alloc_token_str(t_token token);
void				token_to_expand_str(t_string *str, t_token token);
bool				token_is_redir_op(t_token token);
bool				token_is_connector(t_token token);
t_redirect_type		tok_kind_to_redir_type(t_token_kind kind);
t_token				lexer_peek_next_token(t_lexer *lexer);
bool				lexer_check_parens(t_lexer *lexer);
int					is_whitespace(char c);

#endif /*_LEXER_H_ */
