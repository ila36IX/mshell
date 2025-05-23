#ifndef _LEXER_H_
#define _LEXER_H_
#include "includes.h"

typedef enum {
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
    TOKEN_INVALID,
} t_token_kind;

typedef struct s_lexer {
    const char *content;
    size_t content_len;
    size_t cursor;
} t_lexer;

/**
 * t_token - a slice of the user input that represent a valid token
 *
 * @kind: type of this token
 * @text: Pointer of the beginning of the token
 * @text_len: size of this token, do not expect null charachter in the end, this is only a slice
 * @ws-after: Is this token followed by a white space?
 */
typedef struct s_token {
    t_token_kind kind;
    const char *text;
    size_t text_len;
    bool whitespace_before; /* is this token have a white space before it */
} t_token;

t_lexer lexer_new(const char *content, size_t size);
t_token lexer_next_token(t_lexer *l);
const char *token_kind_name(t_token_kind kind);
void	print_token(t_token token);

#endif /*_LEXER_H_ */
