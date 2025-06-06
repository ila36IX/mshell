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

t_ast *last_ast(t_ast *ast)
{
	while (ast && ast->next)
		ast = ast->next;
	return (ast);
}

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
	if (ast->simple_cmd._buff_size == ast->simple_cmd.argc)
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

void ast_add_back(t_ast **head, t_ast *new)
{
	if (!head || !new)
		return;
	while (*head)
		head = &(*head)->next;
	*head = new;
}

t_ast *ast_try_add_connector(t_ast **ast_head, t_lexer *lexer)
{
	t_ast  *ast;
	t_token token;

	token = lexer_peek_next_token(lexer);
	if (token.kind != TOKEN_PIPE && token.kind != TOKEN_OR &&
	    token.kind != TOKEN_AND)
		return (NULL);
	if (!last_ast(*ast_head))
	{
		printf(ERR_UNEXPECTED_TOK, alloc_token_str(token));
		UNIMPLEMENTED("Handle errors");
	}
	if (last_ast(*ast_head)->type != AST_SIMPLE_COMMAND && last_ast(*ast_head)->type != AST_SUBSHELL)
	{
		printf(ERR_UNEXPECTED_TOK, alloc_token_str(token));
		UNIMPLEMENTED("Handle errors");
	}
	token = lexer_next_token(lexer);
	ast = ft_calloc(1, sizeof(t_ast));
	ast->next = NULL;
	ast->type = AST_CONNECTOR;
	if (token.kind == TOKEN_OR)
		ast->connector = CONNECTOR_OR;
	else if (token.kind == TOKEN_AND)
		ast->connector = CONNECTOR_AND;
	else if (token.kind == TOKEN_PIPE)
		ast->connector = CONNECTOR_PIPE;
	ast_add_back(ast_head, ast);
	return (ast);
}

t_ast *ast_try_add_simple_cmd(t_ast **ast_head, t_lexer *lexer)
{
	t_ast  *ast;
	t_token token;

	token = lexer_peek_next_token(lexer);
	if (!token_is_word(token) && !token_is_redir_op(token))
		return (NULL);
	ast = init_ast_simple_cmd();
	ast_add_back(ast_head, ast);
	while (token.kind)
	{
		if (token_is_word(token))
			ast_simple_cmd_add_arg(ast, lexer);
		else if (token_is_redir_op(token))
			ast_add_redirct(ast, lexer);
		else
			break;
		token = lexer_peek_next_token(lexer);
	}
	return (ast);
}
t_ast *parse(t_lexer *lexer);

void skip_nested_parens(t_lexer *lexer)
{
	t_token token;
	int	depth;

	token = lexer_next_token(lexer);
	depth = 1;
	while (token.kind)
	{
		if (token.kind == TOKEN_OPAREN)
			depth++;
		else if (token.kind == TOKEN_CPAREN)
			depth--;
		if (token.kind == TOKEN_CPAREN && depth == 0)
			break;
		token = lexer_next_token(lexer);
	}
	if (depth > 0)
	{
		printf(ERR_UNEXPECTED_TOK, "(");
		UNIMPLEMENTED("Handle unclosing parentheses errors");
	}
	else if (depth < 0)
	{
		printf(ERR_UNEXPECTED_TOK, ")");
		UNIMPLEMENTED("Handle unclosing parentheses errors");
	}
}

t_lexer subshell_new_lexer(t_lexer *lexer)
{
	size_t	cursor_loc;
	t_lexer sub_lexer;
	size_t lexer_size;

	lexer_next_token(lexer); /* skip open parent */
	cursor_loc = lexer->cursor;
	skip_nested_parens(lexer);
	lexer_size = lexer->cursor - cursor_loc - 1;
	sub_lexer = lexer_new(&lexer->content[cursor_loc], lexer_size);
	return (sub_lexer);
}

t_ast *init_ast_subshell(void)
{
	t_ast *ast;

	ast = ft_calloc(1, sizeof(t_ast));
	ast->type = AST_SUBSHELL;
	ast->redir_size = 0;
	ast->redir = ft_calloc(ARRAY_INIT_SIZE, sizeof(t_redirect));
	ast->_buff_size = ARRAY_INIT_SIZE;
	return (ast);
}


t_ast *ast_try_add_subshell(t_ast **ast_head, t_lexer *lexer)
{
	t_ast  *ast;
	t_token token;
	t_lexer sub_lexer;

	token = lexer_peek_next_token(lexer);
	if (token.kind == TOKEN_CPAREN)
	{
		printf(ERR_UNEXPECTED_TOK, ")");
		TODO("Handle Errors\n");
	}
	if (token.kind != TOKEN_OPAREN)
		return (NULL);
	if (last_ast(*ast_head) && last_ast(*ast_head)->type != AST_CONNECTOR)
	{
		printf(ERR_UNEXPECTED_TOK, ")");
		UNIMPLEMENTED("Syntax error\n");
	}
	ast = init_ast_subshell();
	sub_lexer = subshell_new_lexer(lexer);
	ast->subshell = parse(&sub_lexer);
	if (ast->subshell == NULL)
	{
		printf(ERR_UNEXPECTED_TOK, ")");
		UNIMPLEMENTED("Syntax error\n");
	}
	token = lexer_peek_next_token(lexer);
	while (token_is_redir_op(token))
	{
		ast_add_redirct(ast, lexer);
		token = lexer_peek_next_token(lexer);
	}
	ast_add_back(ast_head, ast);
	return (ast);
}

t_ast *parse(t_lexer *lexer)
{
	t_ast *ast;

	ast = NULL;
	while (lexer_peek_next_token(lexer).kind)
	{
		ast_try_add_simple_cmd(&ast, lexer);
		ast_try_add_connector(&ast, lexer);
		ast_try_add_subshell(&ast, lexer);
	}
	return (ast);
}
