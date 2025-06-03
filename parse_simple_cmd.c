#include "lexer.h"
#include "libft/libft.h"
#include "main.h"
#include "print_ast.h"
#include "types.h"
#include <stdbool.h>

/**
 * lexer_peek_next_token - Get the next token without moving the cursor
 *
 * @lexer: pointer to the lexer
 * Return: next token
 */
t_token lexer_peek_next_token(t_lexer *lexer)
{
	t_token token;
	size_t	cursor_location;

	cursor_location = lexer->cursor;
	token = lexer_next_token(lexer);
	lexer->cursor = cursor_location;
	return (token);
}

#define DYNAMIC_ARRAY_INIT_SIZE 16

bool next_token_is_joinable(t_lexer *lexer)
{
	t_token token;

	token = lexer_peek_next_token(lexer);
	if (token.kind == TOKEN_DQ || token.kind == TOKEN_SQ ||
	    token.kind == TOKEN_WORD)
	{
		if (token.whitespace_before == false)
			return (true);
		else
			return (false);
	}
	return (false);
}

char *alloc_token_str(t_token token)
{
	return (ft_substr(token.text, 0, token.text_len));
}

bool token_is_word(t_token token)
{
	return (token.kind == TOKEN_DQ || token.kind == TOKEN_SQ ||
		token.kind == TOKEN_WORD);
}
bool token_is_redir_op(t_token token)
{
	return (token.kind == TOKEN_OUT || token.kind == TOKEN_IN ||
		token.kind == TOKEN_HEREDOC || token.kind == TOKEN_APPEND);
}
/**
 */
char *lexer_next_zip_word(t_lexer *lexer)
{
	char   *zip_word;
	char   *tmp_zip_word;
	t_token token;

	token = lexer_next_token(lexer);
	zip_word = alloc_token_str(token);
	while (next_token_is_joinable(lexer))
	{
		token = lexer_next_token(lexer);
		tmp_zip_word = alloc_token_str(token);
		zip_word = ft_strjoin(zip_word, tmp_zip_word);
	}
	return (zip_word);
}

t_redirect_type tok_kind_to_redir_type(t_token_kind kind)
{
	if (kind == TOKEN_OUT)
		return (REDIR_TYPE_OUT);
	else if (kind == TOKEN_IN)
		return (REDIR_TYPE_IN);
	else if (kind == TOKEN_APPEND)
		return (REDIR_TYPE_APPEND);
	else if (kind == TOKEN_HEREDOC)
		return (REDIR_TYPE_HEREDOC);
	else
	{
		UNREACHABLE("Undefind token kind!");
	}
}

#define ERR_MSG_REDIRECT_TERGET "msh: syntax error near unexpected token `%s'\n"


void ast_simple_cmd_add_arg(t_ast *ast, t_lexer *lexer)
{
	size_t buff_size;
	char **buff;
	size_t    i;

	if (ast->type != AST_SIMPLE_COMMAND)
	{
		PANIC("Wrong ast type!");
		return;
	}
	if (ast->simple_cmd->_buff_size - 1 == ast->simple_cmd->argc)
	{
		buff_size = ast->simple_cmd->argc * 2;
		buff = ft_calloc(buff_size, sizeof(char *));
		i = 0;
		while (i < ast->simple_cmd->argc)
		{
			buff[i] = ast->simple_cmd->argv[i];
			i++;
		}
		ast->simple_cmd->argv = buff;
		ast->simple_cmd->_buff_size = buff_size;
	}
	ast->simple_cmd->argv[ast->simple_cmd->argc++] = lexer_next_zip_word(lexer);
}

void	init_ast_redirect(t_ast *ast)
{
	ast->redir_size = 0;
	ast->redir = ft_calloc(DYNAMIC_ARRAY_INIT_SIZE, sizeof(t_redirect));
	ast->_buff_size = DYNAMIC_ARRAY_INIT_SIZE;
}

void	init_ast_simple_cmd(t_ast *ast)
{
	ast->simple_cmd = ft_calloc(1, sizeof(t_simple_cmd));
	ast->simple_cmd->argv = ft_calloc(DYNAMIC_ARRAY_INIT_SIZE, sizeof(char *));
	ast->simple_cmd->_buff_size = DYNAMIC_ARRAY_INIT_SIZE;
}

void ast_add_redirct(t_ast *ast, t_lexer *lexer)
{
	size_t	    buff_size;
	t_redirect *buff;
	t_token	    token;
	size_t	    i;

	if (ast->_buff_size - 1 == ast->redir_size)
	{
		buff_size = ast->redir_size * 2;
		buff = ft_calloc(buff_size, sizeof(t_redirect));
		i = 0;
		while (i < ast->redir_size)
		{
			buff[i] = ast->redir[i];
			i++;
		}
		ast->redir = buff;
		ast->_buff_size = buff_size;
	}
	token = lexer_next_token(lexer);
	ast->redir[ast->redir_size].type = tok_kind_to_redir_type(token.kind);
	token = lexer_peek_next_token(lexer);
	if (token_is_word(token) == false)
	{
		printf(ERR_MSG_REDIRECT_TERGET, alloc_token_str(token));
		TODO("hanlde redirection errors");
	}
	ast->redir[ast->redir_size++].target = lexer_next_zip_word(lexer);
}
// ast->redir[ast->redir_size].type = tok_kind_to_redir_type(lexer_next_token(lexer).kind);
// if (token_is_word(lexer_peek_next_token(lexer)) == false)
// {
// 	token = lexer_next_token(lexer);
// 	printf(ERR_MSG_REDIRECT_TERGET,
// 	       token_to_str(token));
// 	TODO("hanlde redirection errors");
// }
// ast->redir[ast->redir_size].target =
//     lexer_next_zip_word(lexer);
// ast->redir_size++;

void parse_simple_cmd(t_lexer *lexer)
{
	t_ast  *ast;
	t_token token;

	ast = ft_calloc(1, sizeof(t_ast));
	ast->type = AST_SIMPLE_COMMAND;
	init_ast_redirect(ast);
	init_ast_simple_cmd(ast);
	token = lexer_peek_next_token(lexer);
	while (token.kind)
	{
		if (token_is_word(token))
			ast_simple_cmd_add_arg(ast, lexer);
		else if (token_is_redir_op(token))
			ast_add_redirct(ast, lexer);
		else
		{
			token = lexer_next_token(lexer);
			TODO("handle operators tokens (|, &&, ||)");
		}
		token = lexer_peek_next_token(lexer);
	}
	print_ast(ast);
}
