#include "ast_parser.h"

void	ast_redirct_realloc(t_ast *ast)
{
	size_t		buff_size;
	t_redirect	*buff;
	size_t		i;

	buff_size = ast->redir_size * 2;
	buff = ft_calloc(buff_size, sizeof(t_redirect));
	i = 0;
	while (i < ast->redir_size)
	{
		buff[i] = ast->redir[i];
		i++;
	}
	ast->redir = buff;
	ast->redir_capacity = buff_size;
}

char *read_from_herdoc(t_word word)
{
	t_string str;
	char *delim;
	char *line;

	str = string_init();
	delim = ft_substr(word.text, 0, word.len);
	quote_removal(delim, ft_strlen(delim));
	while (true)
	{
		line = readline("> ");
		if (line == NULL)
			break;
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break;
		}
		string_append_cstr(&str, line);
		string_append_cstr(&str, "\n");
	}
	return (str.buff);
}

/**
 * ast_add_redirct - add redirect with its target to ast node
 *
 * @ast: node to a valid ast
 * @lexe: Next token expected to be redirect op
 *
 * Return: false if the target is invalid, true if target is valid
 * invalid ast node will be added
 */
bool	ast_add_redirct(t_ast **ast_head, t_ast *ast, t_lexer *lexer)
{
	t_token	token;
	t_word	target;

	if (ast->redir_capacity == ast->redir_size)
		ast_redirct_realloc(ast);
	token = lexer_next_token(lexer);
	ast->redir[ast->redir_size].type = tok_kind_to_redir_type(token.kind);
	token = lexer_next_token(lexer);
	if (token.kind != TOKEN_WORD)
	{
		ast_add_error(ast_head, token.text, token.text_len);
		return (false);
	}
	target.len = token.text_len;
	target.text = token.text;
	ast->redir[ast->redir_size].word_target = target;
	if (ast->redir[ast->redir_size].type == REDIR_TYPE_HEREDOC)
		ast->redir[ast->redir_size].target = read_from_herdoc(target);
	ast->redir_size++;
	return (true);
}
