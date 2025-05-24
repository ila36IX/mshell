/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consturct_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:37:32 by sboukiou          #+#    #+#             */
/*   Updated: 2025/05/24 15:09:32 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

static void	redir_push_back(t_redirect **head, t_redirect_type type, const char *target)
{
	printf("Called redir_push_back\n");
	t_redirect	*new;
	t_redirect	*tmp;

	if (!head)
	{
		UNREACHABLE("No Redirection head\n");
		return ;
	}
	printf("new redir node created\n");
	new = (t_redirect *)malloc(sizeof(t_redirect));
	if (!new)
	{
		UNREACHABLE("Malloc failed\n");
		return ;
	}

	new = (t_redirect *)malloc(sizeof(t_redirect));
	new->type = type;
	new->target = (char *)target;
	new->next = NULL;
	printf("new redir node filled\n");
	if (*head == NULL)
	{
		printf("head node assigned new -> first node\n");
		*head = new;
		return ; 
	}
	printf("pushing at the end of the redir nodes\n");
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	printf("tmp assigned to iterate throughout the list\n");
}

static t_redirect_type get_redirection_type(t_token token)
{
	printf("Called get_redirection_type\n");
	if (token.kind == TOKEN_APPEND)
		return (REDIR_TYPE_APPEND);
	if (token.kind == TOKEN_HEREDOC)
		return (REDIR_TYPE_HEREDOC);
	if (token.kind == TOKEN_IN)
		return (REDIR_TYPE_IN);
	if (token.kind == TOKEN_OUT)
		return (REDIR_TYPE_OUT);
	UNREACHABLE("token kind has to be REDIR only\n");
}

static void	append_redir(t_token token, t_lexer *lexer, t_cmd *cmd)
{
	printf("Called append_redirection\n");
	t_redirect_type type;
	t_token	target;

	if (!cmd || !lexer)
	{
		UNREACHABLE("Cmd null !!\n");
		return ;
	}
	type = get_redirection_type(token);
	target = lexer_next_token(lexer);
	redir_push_back(&cmd->redir, type, target.text);
}

static bool	is_token_redir(t_token token)
{
	printf("Called is_token_redir\n");
	if (token.kind == TOKEN_APPEND)
		return (true);
	if (token.kind == TOKEN_HEREDOC)
		return (true);
	if (token.kind == TOKEN_IN)
		return (true);
	if (token.kind == TOKEN_OUT)
		return (true);
	return (false);
}

static char *str_redir_type(t_redirect_type type)
{
	if (type == REDIR_TYPE_APPEND)
		return ("REDIR_TYPE_APPEND");
	if (type == REDIR_TYPE_HEREDOC)
		return ("REDIR_TYPE_HEREDOC");
	if (type == REDIR_TYPE_IN)
		return ("REDIR_TYPE_IN");
	if (type == REDIR_TYPE_OUT)
		return ("REDIR_TYPE_OUT");
	return ("INVALID");
}

static void	print_cmd(t_cmd cmd)
{
	printf("Called print_cmd\n");
	while (cmd.argv)
	{
		printf("[ARGV]: %s\n", *cmd.argv);
		cmd.argv++;
	}
	while (cmd.redir)
	{
		printf("[REDIRECTION]: %s  %s %p\n", str_redir_type(cmd.redir->type), cmd.redir->target, cmd.redir->next);
			cmd.redir++;
	}
	printf("finished\n");
}

void	construct_cmd(t_lexer *lexer, t_cmd *cmd)
{
	t_token	token;

	if (!lexer)
	{
		UNREACHABLE("Lexer NULL !\n");
		return ;
	}
	;
	token = lexer_next_token(lexer);
	while (token.kind != TOKEN_NULL)
	{
		print_token(token);
		if (is_token_redir(token))
			append_redir(token, lexer, cmd);
		token  = lexer_next_token(lexer);
	}
	print_cmd(*cmd);
}
