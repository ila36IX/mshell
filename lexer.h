#ifndef _LEXER_H_
# define _LEXER_H_
# include "types.h"

typedef enum
{
	TOKEN_NULL = 0,
	TOKEN_IN,
	TOKEN_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_OR,
	TOKEN_AND,
	TOKEN_PIPE,
	TOKEN_SQ,
	TOKEN_DQ,
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
 * @whitespace_before: Is this token followed by a white space?
 */
typedef struct s_token
{
	t_token_kind	kind;
	const char		*text;
	size_t			text_len;
	bool whitespace_before;
}					t_token;

t_lexer				lexer_new(const char *content, size_t size);
t_token				lexer_next_token(t_lexer *l);
const char			*token_kind_name(t_token_kind kind);
void				print_token(t_token token);
void	print_lexer_tokens(t_lexer *lexer);
char *alloc_token_str(t_token token);
bool token_is_word(t_token token);
bool token_is_redir_op(t_token token);
bool token_is_operator(t_token token);
char *lexer_next_zip_word(t_lexer *lexer);
bool next_token_is_joinable(t_lexer *lexer);
t_redirect_type tok_kind_to_redir_type(t_token_kind kind);
t_token lexer_peek_next_token(t_lexer *lexer);

#endif /*_LEXER_H_ */
