/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   consturct_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 13:37:32 by sboukiou          #+#    #+#             */
/*   Updated: 2025/05/24 13:59:33 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./main.h"

static void	redir_push_back(t_redirect **head, t_redirect_type type, char *target)
{
	t_redirect	*new;
	t_redirect	*tmp;

	if (!head)
	{
		UNREACHABLE("No Redirection head\n");
		return ;
	}
	if (!(*head))
	{
		(*head)->type = type;
		(*head)->target = target;
		(*head)->next = NULL;
		return ;
	}
	new = (t_redirect *)malloc(sizeof(t_redirect));
	if (!new)
	{
		UNREACHABLE("Malloc failed\n");
		return ;
	}

		new->type = type;
		new->target = target;
		new->next = NULL;
	tmp = *head;
	while (tmp->next)
		tmp =  tmp->next;
	tmp->next = new;
}

static bool	is_token_redir(t_token token)
{
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

static void	append_redir(t_token token, t_lexer *lexer, t_cmd *cmd)
{
	t_redirect	*new_redir;
	if (!cmd || !lexer)
	{
		UNREACHABLE("Cmd null !!\n");
		return ;
	}
	TODO("Push back new redirection to cmd redir\n");
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
	}
}
