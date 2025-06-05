#include "lexer.h"
#include "libft/libft.h"
#include "main.h"
#include "memory.h"
#include "print_ast.h"
#include "types.h"
#include <readline/history.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>

#define ARRAY_INIT_SIZE 16
#define ERR_UNEXPECTED_TOK "msh: syntax error near unexpected token `%s'\n"

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

bool token_is_operator(t_token token)
{
	return (token.kind == TOKEN_PIPE || token.kind == TOKEN_AND ||
		token.kind == TOKEN_OR);
}

bool next_token_is_joinable(t_lexer *lexer)
{
	t_token token;

	token = lexer_peek_next_token(lexer);
	if (token_is_word(token))
		return (token.whitespace_before == false);
	return (false);
}

char *alloc_token_str(t_token token)
{
	/* NOTE: Expand will happen here */
	return (ft_substr(token.text, 0, token.text_len));
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

void ast_simple_cmd_realloc(t_ast *ast)
{
	size_t buff_size;
	char **buff;
	size_t i;

	buff_size = ast->simple_cmd.argc * 2;
	buff = ft_calloc(buff_size, sizeof(char *));
	i = 0;
	while (i < ast->simple_cmd.argc)
	{
		buff[i] = ast->simple_cmd.argv[i];
		i++;
	}
	ast->simple_cmd.argv = buff;
	ast->simple_cmd._buff_size = buff_size;
}

void ast_simple_cmd_add_arg(t_ast *ast, t_lexer *lexer)
{
	char *arg;

	if (ast->type != AST_SIMPLE_COMMAND)
	{
		PANIC("Wrong ast type!");
		return;
	}
	if (ast->simple_cmd._buff_size - 1 == ast->simple_cmd.argc)
		ast_simple_cmd_realloc(ast);
	arg = lexer_next_zip_word(lexer);
	ast->simple_cmd.argv[ast->simple_cmd.argc++] = arg;
}

t_ast *init_ast_simple_cmd(void)
{
	t_ast *ast;

	ast = ft_calloc(1, sizeof(t_ast));
	ast->type = AST_SIMPLE_COMMAND;
	ft_bzero(&ast->simple_cmd, sizeof(t_simple_cmd));
	ast->simple_cmd.argv = ft_calloc(ARRAY_INIT_SIZE, sizeof(char *));
	ast->simple_cmd._buff_size = ARRAY_INIT_SIZE;
	ast->redir_size = 0;
	ast->redir = ft_calloc(ARRAY_INIT_SIZE, sizeof(t_redirect));
	ast->_buff_size = ARRAY_INIT_SIZE;
	return (ast);
}

void ast_redirct_realloc(t_ast *ast)
{
	size_t	    buff_size;
	t_redirect *buff;
	size_t	    i;

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

void ast_add_redirct(t_ast *ast, t_lexer *lexer)
{
	t_token token;
	char   *target;

	if (ast->_buff_size == ast->redir_size)
		ast_redirct_realloc(ast);
	token = lexer_next_token(lexer);
	ast->redir[ast->redir_size].type = tok_kind_to_redir_type(token.kind);
	token = lexer_peek_next_token(lexer);
	if (token_is_word(token) == false)
	{
		printf(ERR_UNEXPECTED_TOK, alloc_token_str(token));
		TODO("hanlde redirection errors");
	}
	target = lexer_next_zip_word(lexer);
	ast->redir[ast->redir_size++].target = target;
}

t_ast *ast_add_connector(t_ast *ast, t_lexer *lexer)
{
	t_ast  *ast_node;
	t_ast  *next_ast = init_ast_simple_cmd();
	t_token token;

	token = lexer_next_token(lexer);
	if (!ast)
	{
		printf(ERR_UNEXPECTED_TOK, alloc_token_str(token));
		TODO("hanlde redirection errors");
	}
	ast_node = ft_calloc(1, sizeof(t_ast));
	ast_node->next = NULL;
	ast_node->type = AST_CONNECTOR;
	if (token.kind == TOKEN_OR)
		ast_node->connector = CONNECTOR_OR;
	else if (token.kind == TOKEN_AND)
		ast_node->connector = CONNECTOR_AND;
	else if (token.kind == TOKEN_PIPE)
		ast_node->connector = CONNECTOR_PIPE;
	else
	{
		UNREACHABLE("next token suppose to be one of the connecoters")
	}
	while (ast->next)
		ast = ast->next;
	ast->next = ast_node;
	ast_node->next = next_ast;
	return (next_ast);
}

size_t untill_close_paren(t_lexer *lexer)
{
	size_t	cursor_loc;
	size_t	in_between;
	t_token token;

	lexer_next_token(lexer); /* skip open parent */
	cursor_loc = lexer->cursor;
	token = lexer_next_token(lexer);
	while (token.kind && token.kind != TOKEN_CPAREN)
	{
		if (token.kind == TOKEN_OPAREN)
		{
			TODO("Handle recursive parentheses");
		}
		token = lexer_next_token(lexer);
	}
	if (!token.kind)
	{
		printf(ERR_UNEXPECTED_TOK, "(");
		UNIMPLEMENTED("Handle unclosing parentheses errors");
	}
	in_between = lexer->cursor - cursor_loc;
	if (lexer->cursor - cursor_loc == 0)
	{
		UNIMPLEMENTED("Between parentheses is empty\n");
	}
	in_between--;
		
	lexer->cursor = cursor_loc;
	return (in_between);
}

t_ast *parse_simple_cmd(t_lexer *lexer);

t_ast *parse_subshell(t_ast *ast, t_lexer *lexer)
{
	t_ast *_ast;


	print_lexer_tokens(lexer);
	_ast = ft_calloc(1, sizeof(t_ast));
	_ast->type = AST_SUBSHELL;
	_ast->subshell = parse_simple_cmd(lexer);
	ast->next = _ast;
	_ast->next = NULL;
	return (_ast);
}

t_ast *parse_simple_cmd(t_lexer *lexer)
{
	t_ast  *ast;
	t_ast  *ast_head;
	t_lexer sub_lexer;
	t_token token;

	ast = init_ast_simple_cmd();
	ast_head = ast;
	token = lexer_peek_next_token(lexer);
	while (token.kind)
	{
		if (token.kind == TOKEN_OPAREN)
		{
			size_t parent_size = untill_close_paren(lexer);
			printf("There is %zu between parants\n",
			       parent_size);
			sub_lexer = lexer_new(&lexer->content[lexer->cursor],
					      parent_size);
			ast = parse_subshell(ast, &sub_lexer);
			lexer->cursor += parent_size + 1;
		}
		else if (token_is_word(token))
			ast_simple_cmd_add_arg(ast, lexer);
		else if (token_is_redir_op(token))
			ast_add_redirct(ast, lexer);
		else if (token_is_operator(token))
			ast = ast_add_connector(ast, lexer);
		else
		{
			TODO("handle other tokens (|, &&, ||, (, ),INVALID)");
		}
		token = lexer_peek_next_token(lexer);
	}
	// print_ast(ast_head);
	return (ast_head);
}

t_ast *parse(t_lexer *lexer)
{
	t_ast  *ast;
	t_token token;

	ast = ft_calloc(1, sizeof(t_ast));
	token = lexer_peek_next_token(lexer);
	while (token.kind)
	{
		if (token_is_redir_op(token))
			ast_add_redirct(ast, lexer);
		else if (token.kind == TOKEN_OPAREN)
		{
			size_t parent_size = untill_close_paren(lexer);
			t_lexer sub_lexer;
			sub_lexer = lexer_new(&lexer->content[lexer->cursor], parent_size);
			ast = parse(&sub_lexer);
			lexer->cursor += parent_size + 1;
		}
		else
			token = lexer_next_token(lexer);
	}
	return (ast);
}
