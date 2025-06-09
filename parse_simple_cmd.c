#include "parser.h"
#include "types.h"

void	ast_simple_cmd_realloc(t_ast *ast)
{
	size_t	buff_size;
	char	**buff;
	size_t	i;

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

void	ast_simple_cmd_add_arg(t_ast *ast, t_lexer *lexer)
{
	char	*arg;

	if (ast->type != AST_SIMPLE_COMMAND)
	{
		UNREACHABLE("Wrong ast type!");
		return ;
	}
	if (ast->simple_cmd._buff_size == ast->simple_cmd.argc)
		ast_simple_cmd_realloc(ast);
	arg = lexer_next_zip_word(lexer);
	ast->simple_cmd.argv[ast->simple_cmd.argc++] = arg;
}

t_ast	*init_ast_simple_cmd(void)
{
	t_ast	*ast;

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

bool	is_valid_simple_cmd(t_ast **ast_head, t_lexer *lexer)
{
	char	*token_str;

	if (!last_ast(*ast_head))
		return (true);
	if (last_ast(*ast_head)->type != AST_CONNECTOR)
	{
		token_str = alloc_token_str(lexer_peek_next_token(lexer));
		ast_add_error(ast_head, ERR_UNEXPECTED_TOK, token_str);
		return (false);
	}
	return (true);
}

t_ast	*ast_add_simple_cmd(t_ast **ast_head, t_lexer *lexer)
{
	t_ast	*ast;
	t_token	token;

	token = lexer_peek_next_token(lexer);
	if (!is_valid_simple_cmd(ast_head, lexer))
		return (NULL);
	ast = init_ast_simple_cmd();
	ast_add_back(ast_head, ast);
	while (token.kind)
	{
		if (token_is_word(token))
			ast_simple_cmd_add_arg(ast, lexer);
		else if (token_is_redir_op(token))
		{
			if (!ast_add_redirct(ast_head, ast, lexer))
				return (ast);
		}
		else
			break ;
		token = lexer_peek_next_token(lexer);
	}
	return (ast);
}
