/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sboukiou <sboukiou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:24:58 by sboukiou          #+#    #+#             */
/*   Updated: 2025/05/15 13:33:08 by sboukiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include "./includes.h"

typedef enum e_connector
{
	OP_AND,
	OP_PIPE,
	OP_OR
}						t_connector;

typedef enum e_ast_type
{
	AST_SUBSHELL,
	AST_SIMPLE_COMMAND,
	AST_CONNECTOR,
}						t_ast_type;

typedef enum e_redirect_type
{
	REDIR_TYPE_IN,
	REDIR_TYPE_OUT,
	REDIR_TYPE_APPEND,
	REDIR_TYPE_HEREDOC
}						t_redirect_type;

/**
 * t_redirect - Mimics the behavior of dynamic array
 * to avoid the overhead caused when using linked-lists
 *
 * @type: Integer represinting redirection type see t_redirect_type
 * @target: Filename for <, >, >> Delimiter for <<
 * @redirect_size: Current size of the array.
 */
typedef struct s_redirect
{
	t_redirect_type		type;
	char				*target;
	size_t				redirec_size;
}						t_redirect;

/**
 * NOTE: ADD docs here
 * 
 */
typedef struct s_simple_cmd
{
	char				**argv;
	int					argc;
}						t_simple_cmd;

/*
 * NOTE: add docs here....
 */
typedef struct s_ast
{
	t_ast_type			type;
	union
	{
		t_connector		connecter;
		t_simple_cmd	*simple_cmd;
		struct s_ast	*subshell;
	};
	t_redirect			*redir;
	struct s_ast		*next;
}						t_ast;

#endif /* TYPES_H */
