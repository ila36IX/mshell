#ifndef _LEXER_H_
#define _LEXER_H_
#include "includes.h"

typedef enum {
    TOKEN_TYPE_IN,
    TOKEN_TYPE_OUT,
    TOKEN_TYPE_APPEND,
    TOKEN_TYPE_HEREDOC,
    TOKEN_TYPE_OR,
    TOKEN_TYPE_AND,
    TOKEN_TYPE_PIPE,
    TOKEN_TYPE_SQ,
    TOKEN_TYPE_DQ,
} t_token_kind;

typedef struct s_lexer {
    const char *content;
    const char *content_len;
    size_t cursor;
} t_lexer;

t_lexer lexer_new(const char *content);
t_token_kind lexer_next_token(t_lexer *l);
const char *token_kind_name(t_token_kind kind);
void	print_token(t_token_kind kind);

#endif /*_LEXER_H_ */
